/*
 * MolSim.cpp
 *
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"

#include "Particle.h"
#include "ParticleContainer.h"
#include "ParticleGenerator.h"
#include "Calculation.h"
#include "Plotter.h"
#include "BoundaryCondition.h"
#include "cppunit/Tester.h"
#include "input.h"

#include <cppunit/ui/text/TestRunner.h>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include <memory>   // std::auto_ptr
#include <iostream>

#include <iostream>
#include <cstdlib>
#include <sys/timeb.h>
#include <assert.h>

using namespace std;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/**
 * values can be set at startup by passing params
 */
double start_time = 0;
double end_time; 
double delta_t;
double sigma;
double epsilon;


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
Plotter *plotter = &vtk_plotter;
OutflowBoundary outflowBoundary;
ReflectingBoundary reflectingBoundary;
BoundaryCondition *boundaryCondition = &reflectingBoundary;

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
	if(argc != 2) {
		showUsage();
		exit(-1);
	}

	auto_ptr<input_t> inp;
	try {
		inp =  (input (argsv[1]));
	} catch (const xml_schema::exception& e){
    	cerr << e << endl;
    	LOG4CXX_FATAL(loggerMain, e);
    	LOG4CXX_FATAL(loggerMain, "XML Parsing error, shut down");
    	exit(-1);
  	}

    //assign values from xml file
    delta_t = inp->delta_t();
    end_time = inp->tend();
    epsilon = inp->epsilon();
    sigma = inp->sigma();
    int cutOff = inp->LinkedCellDomain().cutoff();
    //epsilon = 5.0;
    //sigma = 1.0;
    std::cout << "Epsilon: " << epsilon << " Sigma: " << sigma << " Cutoff: "<< cutOff << std::endl;
    assert(delta_t>0);
    assert(end_time>0);
    assert(epsilon>0);
    assert(sigma>0);

	ParticleGenerator pg;
	int* length = new int;

	//Particle** pa = pg.readFile(length, inp);
	std::vector<Particle*> pa = pg.readFile(length, inp);

	//Initialize LCDomain
	std::vector<int> domainSize(3,0);
	//int cutOff = 1;
	assert(cutOff>0);
	domainSize[0] = inp->LinkedCellDomain().dimension().x();
	assert(domainSize[0]>0);
	domainSize[1] = inp->LinkedCellDomain().dimension().y();
	assert(domainSize[1]>0);
	domainSize[2] = inp->LinkedCellDomain().dimension().z();
	assert(domainSize[2]>0);
	LCDomain lcDomain(&domainSize,cutOff, cutOff);
	std::cout << "DomainSize " << domainSize[0] << " " << domainSize[1] << " " << domainSize[2] << " " << std::endl;
	lcDomain.insertParticles(pa);
	/*for(int i = 0; i < pa.size(); i++){
		lcDomain.insertParticle(pa[i]);
	}*/

	ParticleContainer pc(*length);
	pc.setParticles(pa);

	calculation->setDeltaT(delta_t);
	calculation->setParticleContainer(pc);
	calculation->setLcDomain(lcDomain);
	calculation->setEpsilon(epsilon);
	calculation->setSigma(sigma);

	boundaryCondition->setDomainSize(domainSize);
	boundaryCondition->setLCDomain(lcDomain);
	boundaryCondition->setEpsilon(epsilon);
	boundaryCondition->setSigma(sigma);

	plotter->setParticleContainer(pc);
	plotter->setLcDomain(lcDomain);

	//initially calculation of Forces
	calculation->resetForce();
	calculation->calculateForce();


	double current_time = start_time;
	int iteration = 0;
	LOG4CXX_TRACE(loggerMain, "Starting calculation loop..");
	

	int startTime = getMilliCount();
	double accTime = 0;
	LOG4CXX_INFO(loggerMain,"Iteration " << "xx" << " finished. It took: " << "abs" << " (" << "avg" << ") msec" );
	while (current_time < end_time){
		calculation->resetForce();
		boundaryCondition->applyBoundaryCondition(length);
		calculation->calculateAll();

		iteration++;
		if (iteration % inp->frequency() == 0) {
			plotter->plotParticles(iteration, *length);
			int time = getMilliSpan(startTime);
			accTime += time;
			LOG4CXX_INFO(loggerMain, "Iteration " << iteration << " finished. It took: " << time << " (" << (int)(accTime/(iteration/inp->frequency())) << ") msec" );
			startTime = getMilliCount();
		}

		current_time += delta_t;
	}
	LOG4CXX_INFO(loggerMain, "Output successfully written. Terminating...");

	delete length;

	return 0;
}

int getMilliCount(){
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

int getMilliSpan(int nTimeStart){
	int nSpan = getMilliCount() - nTimeStart;
	if(nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}

void showUsage() {
	LOG4CXX_FATAL(loggerMain, "erroneous programm call - program will halt!");
	LOG4CXX_INFO(loggerMain, "Run : ./MolSim inputfile (input file must be of type described in associated xsd file)");
	LOG4CXX_INFO(loggerMain, "Test: ./MolSim -test");
}
