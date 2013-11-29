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
#include "cppunit/Tester.h"

#include <cppunit/ui/text/TestRunner.h>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include <memory>   // std::auto_ptr
#include <iostream>


#include "input.h"

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/**
 * values can be set at startup by passing params
 */
double start_time = 0;
double end_time; 
double delta_t;


/**
 * Logger
 */
LoggerPtr loggerMain(Logger::getLogger( "main"));

/**
 * set algorithm, which should be used for the calculation.
 * The strategy pattern guarantees, that all special implementations are able to compute the requested values.
 */
Sheet2Calc sheet2calc;
Calculation *calculation = &sheet2calc;
VTK vtk_plotter;
Plotter *plotter = &vtk_plotter;

void showUsage();
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

	auto_ptr<input_t> inp =  (input (argsv[1]));
	
	//example how to use XML File
	for (input_t::cuboid_const_iterator ci (inp->cuboid ().begin ());ci != inp->cuboid ().end ();++ci){
    	cout << ci->number().x() << ci->position().y()<< " "<<ci->velocity().z()<<" " << ci->distance()<<endl;
	}

	//cout << "Number: "<< h->cuboid().number().x()<<endl;
	//cout << h->position()<<endl;
    cout << inp->base_output_file()<< " = " << inp->frequency()<<"  "<<inp->delta_t()<<endl;
    cout << inp->tend()<<endl;
    cout << inp->input_file()<<endl;

 	//end

    //assign values from xml file
    delta_t = inp->delta_t();
    end_time = inp->tend();




	ParticleGenerator pg;
	int* length = new int;

	Particle** pa = pg.readFile(length, inp);
	
	ParticleContainer pc(*length);
	delete length;
	pc.setParticles(pa);

	calculation->setDeltaT(delta_t);
	calculation->setParticleContainer(pc);

	plotter->setParticleContainer(pc);

	//initially calculation of Forces
	calculation->calculateForce();

	double current_time = start_time;
	int iteration = 0;
	LOG4CXX_TRACE(loggerMain, "Starting calculation loop..");
	
	while (current_time < end_time){

		calculation->calculateAll();

		iteration++;
		if (iteration % inp->frequency() == 0) {
			plotter->plotParticles(iteration, *length);
			LOG4CXX_INFO(loggerMain, "Iteration " << iteration << " finished.");
		}

		current_time += delta_t;
	}
	LOG4CXX_INFO(loggerMain, "Output successfully written. Terminating...");
	delete pa;

	return 0;
}


void showUsage() {
	LOG4CXX_FATAL(loggerMain, "erroneous programm call - program will halt!");
	LOG4CXX_INFO(loggerMain, "Run : ./MolSim inputfile (input file must be of type described in associated xsd file)");
	LOG4CXX_INFO(loggerMain, "Test: ./MolSim -test");
}
