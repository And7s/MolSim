/*
 * MolSim.cpp
 *
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "FileReader.h"
#include "Particle.h"
#include "ParticleContainer.h"
#include "ParticleGenerator.h"
#include "Calculation.h"
#include "Plotter.h"

#include <cppunit/ui/text/TestRunner.h>
#include "cppunit/Tester.h"

using namespace std;

/**
 * values can be set at startup by passing params
 */
double start_time = 0;
double end_time = 1000; 
double delta_t = 0.014;
char* filename;

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
	cout << "\n\nMolSim:\n";
	switch(argc) {
		case 4:
			delta_t = atof(argsv[3]);
		case 3:
			end_time = atof(argsv[2]);	
		case 2:
			if(string(argsv[1]) == "-test") {
				CppUnit::TextUi::TestRunner runner;
				runner.addTest( Tester::suite() );
				runner.run();
				exit(1);
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
	pc.setParticles(pa);

	calculation->setDeltaT(delta_t);
	calculation->setParticleContainer(pc);

	plotter->setParticleContainer(pc);

	//initially calculation of Forces
	calculation->calculateForce();

	double current_time = start_time;
	int iteration = 0;
	while (current_time < end_time){

		calculation->calculateAll();

		iteration++;
		if (iteration % 10 == 0) {
			plotter->plotParticles(iteration, *length);
			cout << "Iteration " << iteration << " finished." << endl;
		}

		current_time += delta_t;
	}
	cout << "output written. Terminating..." << endl;
	return 0;
}


void showUsage() {
	cout << "\nMolSim\nError,call program with:\n./MolSim -test                          for testing\nMolSim filename [duration[timestep]]    for running a Simulation\n";
}