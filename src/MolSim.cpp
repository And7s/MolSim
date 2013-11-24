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


using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/**
 * values can be set at startup by passing params
 */
double start_time = 0;
double end_time = 1000; 
double delta_t = 0.014;
char* filename;

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
	switch(argc) {
		case 4:
			delta_t = atof(argsv[3]);
		case 3:
			end_time = atof(argsv[2]);
			if(argc == 3){
				LOG4CXX_WARN(loggerMain, "Input for distance between timestamps missing. Default: " << delta_t);
			}
		case 2:
			if(string(argsv[1]) == "-test") {
				LOG4CXX_TRACE(loggerMain, "Test-mode activated..");
				CppUnit::TextUi::TestRunner runner;
				runner.addTest( Tester::suite() );
				runner.run();
				LOG4CXX_TRACE(loggerMain, "Test finished..");
				exit(0);
			}
			if(argc == 2){
				LOG4CXX_WARN(loggerMain, "Input for distance between timestamps missing. Default: " << delta_t);
				LOG4CXX_WARN(loggerMain, "Input for the duration of the simulation missing Default: " << end_time);
			}
			filename = argsv[1];
			break;
		default:
			showUsage();
			exit(-1);
			break;

	}

	ParticleGenerator pg;
	int* length = new int;
	
	Particle** pa = pg.readFile(filename, length);
	
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
		if (iteration % 10 == 0) {
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
	LOG4CXX_INFO(loggerMain, "Run : ./MolSim inputfile [duration] [step distance]");
	LOG4CXX_INFO(loggerMain, "Test: ./MolSim -test");
}
