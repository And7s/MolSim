/*
 * MolSim.cpp
 *
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "outputWriter/XVFWriter.h"

#include "Particle.h"
#include "ParticleContainer.h"
#include "ParticleGenerator.h"
#include "Calculation.h"
#include "Plotter.h"
#include "BoundaryCondition.h"
#include "cppunit/Tester.h"
#include "input.h"
#include "help_macros.h"
#include "Thermostat.h"
#include "EnvInfl.h"

#include <cppunit/ui/text/TestRunner.h>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include <memory>   // std::auto_ptr
#include <iostream>

#include <iostream>
#include <cstdlib>
#include <sys/timeb.h>

using namespace std;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/**
 * values can be set at startup by passing params
 */
double start_time = 0.0;
double end_time; 
double delta_t;
double sigma;
int type;
double epsilon;
float cutOff;
double gravity = 0.0;
std::string outFile;
std::string dataFile;
std::vector<double>* parameters = new std::vector<double>;
std::vector<Particle*> pa;
std::vector<Particle*> pb;

BoundaryCondition* boundaryCondition;


/**
 * Logger
 */
LoggerPtr loggerMain(Logger::getLogger( "main"));

/**
 * set algorithm, which should be used for the calculation.
 * The strategy pattern guarantees, that all special implementations are able to compute the requested values.
 */
Sheet3Calc sheet3calc;
Calculation *calculation = &sheet3calc;
VTK vtk_plotter;
XVF xvf_plotter;
Plotter *plotter = &vtk_plotter;
Plotter *dataPlotter = &xvf_plotter;
//FileReader fileReader;

/**
 * XML Pointer
 */
auto_ptr<input_t> inp;


void showUsage();
int getMilliCount();
int getMilliSpan(int);
/**
 * lifecycle.. iterates through simulation step by step
 */
int main(int argc, char* argsv[]) {
	//init Logger
	DOMConfigurator::configure("src/Log4cxxConfig.xml");

	LOG4CXX_INFO (loggerMain, "MolSim started..");

	if(argc == 3 && string(argsv[1]) == "-test"){
		LOG4CXX_TRACE(loggerMain, "Single Test-mode activated..");
		CppUnit::TextUi::TestRunner runner;
		runner.addTest( Tester::singleSuite(string(argsv[2])) );
		runner.run();
		LOG4CXX_TRACE(loggerMain, "Test finished..");
		exit(0);
	}

	if(argc == 2 && string(argsv[1]) == "-test") {
		LOG4CXX_TRACE(loggerMain, "Test-mode activated..");
		CppUnit::TextUi::TestRunner runner;
		runner.addTest( Tester::suite() );
		runner.run();
		LOG4CXX_TRACE(loggerMain, "Test finished..");
		exit(0);
	}
	if(argc != 2 && argc != 3) {
		showUsage();
		exit(-1);
	}else{
		try {
			inp =  (input (argsv[1]));
		} catch (const xml_schema::exception& e){
			cerr << e << endl;
			LOG4CXX_FATAL(loggerMain, e);
			LOG4CXX_FATAL(loggerMain, "XML Parsing error, shut down");
			exit(-1);
		}
		if(argc==3){
			pb = xvf_plotter.readParticles(parameters, argsv[2]);
			//assign values from xml file
			delta_t = (*parameters)[0];
			end_time = inp->tend();
			cutOff = (*parameters)[1];
			gravity = (*parameters)[2];
			outFile = inp->base_output_file();
			dataFile = inp->xvf_data_file();
		}else{
			delta_t = inp->delta_t();
			end_time = inp->tend();
			gravity = inp->gravity();
			cutOff = inp->LinkedCellDomain().cutoff();
			outFile = inp->base_output_file();
			dataFile = inp->xvf_data_file();
		}
	}

    ASSERT_WITH_MESSAGE(loggerMain, (delta_t>0), "Invalid delta_t. Please specify first " << delta_t);
    ASSERT_WITH_MESSAGE(loggerMain, (end_time>0), "Invalid end_time. Please specify first " << end_time);
    ASSERT_WITH_MESSAGE(loggerMain, (cutOff>0), "Invalid delta_t. Please specify first " << cutOff);

	ParticleGenerator pg;
	int* length = new int;

	pa = pg.readFile(length, inp);

	if(argc==3){
		pa.insert(pa.end(), pb.begin(), pb.end());
	}

	//Initialize LCDomain
	std::vector<int> domainSize(3,0);
	domainSize[0] = inp->LinkedCellDomain().dimension().x();
	ASSERT_WITH_MESSAGE(loggerMain, (domainSize[0]>0), "Invalid domainSize[0]. Please specify first " << domainSize[0]);
	domainSize[1] = inp->LinkedCellDomain().dimension().y();
	ASSERT_WITH_MESSAGE(loggerMain, (domainSize[1]>0), "Invalid domainSize[1]. Please specify first " << domainSize[1]);
	domainSize[2] = inp->LinkedCellDomain().dimension().z();
	ASSERT_WITH_MESSAGE(loggerMain, (domainSize[2]>0), "Invalid domainSize[2]. Please specify first " << domainSize[2]);
	LCDomain* lcDomain = new LCDomain(&domainSize,cutOff, cutOff);
	lcDomain->insertParticles(pa);

	ParticleContainer pc(*length);
	pc.setParticles(pa);

	calculation->setDeltaT(delta_t);
	calculation->setParticleContainer(pc);
	calculation->setLcDomain(lcDomain);

	EnvInfl::getInstance()->setG(gravity);

	//initiallze boundary conditions
	std::cout << domainSize.size();
	boundaryCondition = new BoundaryCondition(lcDomain, domainSize, inp->dimensions(), inp);
	
	plotter->setParticleContainer(pc);
	plotter->setLcDomain(lcDomain);

	dataPlotter->setLcDomain(lcDomain);

	plotter->plotParticles(0, *length, outFile, *parameters);

	//initially calculation of Forces
	calculation->resetForce();

	//NEW: First calculation step, so that the mean velocity is not zero
	calculation->calculateForce();
	calculation->calculateVelocity();
	calculation->calculatePosition();
	//NEW: First calculation step, so that the mean velocity is not zero

	//init the thermostat
	Thermostat* thermo = new Thermostat(lcDomain, inp);

	double current_time = start_time;
	int iteration = 0;
	LOG4CXX_TRACE(loggerMain, "Starting calculation loop..");
	

	int startTime = getMilliCount();
	double accTime = 0;
	LOG4CXX_INFO(loggerMain,"Iteration " << "xx" << " finished. It took: " << "abs" << " (" << "avg" << ") msec" );
	while (current_time < end_time){
		
		calculation->resetForce();
	
		boundaryCondition->apply();

		calculation->calculateAll();

		iteration++;
		if (iteration % inp->frequency() == 0) {
			plotter->plotParticles(iteration, *length, outFile, *parameters);
			int time = getMilliSpan(startTime);
			accTime += time;
			LOG4CXX_INFO(loggerMain, "Iteration " << iteration << " finished. It took: " << time << " (" << (int)(accTime/(iteration/inp->frequency())) << ") msec" );
			startTime = getMilliCount();
		}
		if(iteration % inp->Thermostats().changed_after() == 0) {
			thermo->change();
		}
		if(iteration % inp->Thermostats().applied_after() == 0) {
			thermo->apply();
		}

		current_time += delta_t;
	}
	LOG4CXX_INFO(loggerMain, "Output successfully written. Elapsed Time: " << (int)(accTime/1000) <<" sec - Terminating...");

	if(inp->plot_data_file()){
		if(argc == 2){
			parameters->push_back(delta_t);
			parameters->push_back(cutOff);
			parameters->push_back(gravity);
		}else{
			(*parameters)[0]= delta_t;
			(*parameters)[1]= cutOff;
			(*parameters)[2]= gravity;
		}

		dataPlotter->plotParticles(0, *length, dataFile, *parameters);
	}
	delete length;

	return 0;
}

/**
 * current system time in msec
 */
int getMilliCount(){
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

/**
 * gather time difference between now and previous timestamp
 * @param nTimeStart previous timestamp -> getMilliCount
 */
int getMilliSpan(int nTimeStart){
	int nSpan = getMilliCount() - nTimeStart;
	if(nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}

void showUsage() {
	LOG4CXX_FATAL(loggerMain, "erroneous programm call - program will halt!");
	LOG4CXX_INFO(loggerMain, "Run : ./MolSim inputfile (input file must be of type described in associated xsd file)");
	LOG4CXX_INFO(loggerMain, "or Run : ./MolSim inputfile datafile.txt (input file must be of type described in associated xsd file)");
	LOG4CXX_INFO(loggerMain, "Test: ./MolSim -test <testnames(optional)>");
}
