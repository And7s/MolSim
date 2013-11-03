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
#include "Calculation.h"
#include "Plotter.h"

using namespace std;

/**
 * values can be set at startup by passing params
 */
double start_time = 0;
double end_time = 1000; 
double delta_t = 0.014;

/**
 * stores the particles. accessed from Calculation by an external reference
 */
std::list<Particle> particles; 

/**
 * set algorithm, which should be used for the calculation.
 * The strategy pattern guarantees, that all special implementations are able to compute the requested values.
 */
Sheet1Calc sheet1calc;
Calculation *calculation = &sheet1calc;
VTK vtk_plotter;
Plotter *plotter = &vtk_plotter;

/**
 * lifecycle.. iterates through simulation step by step
 */
int main(int argc, char* argsv[]) {

	cout << "Hello from MolSim for PSE!" << endl;
	if (argc != 4) {
		cout << "Errounous programme call! " << endl;
		cout << "./molsym filename end_time delta_t" << endl;
		exit(-1);
	}

	end_time = atof(argsv[2]);
	delta_t = atof(argsv[3]);

	FileReader fileReader;
	fileReader.readFile(particles, argsv[1]);
	
	ParticleContainer pc(particles);
	calculation->setDeltaT(delta_t);

	// the forces are needed to calculate x, but are not given in the input file.
	cout << "Initializing forces: " << endl;
	calculation->calculateForce();
	cout << "Forces initialized." << endl;

	double current_time = start_time;

	int iteration = 0;

	 // for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {
		// calculate new x, new f, new v
		calculation->calculateForce();
		calculation->calculatePosition();
		calculation->calculateVelocity();

		iteration++;
		if (iteration % 10 == 0) {
			plotter->plotParticles(iteration, particles.size());
			cout << "Iteration " << iteration << " finished." << endl;
		}
		current_time += delta_t;
	}

	cout << "output written. Terminating..." << endl;
	return 0;
}
/*
void calcAll(){
		// calculate new x
		calculateX();
		// calculate new f
		calculateF();
		// calculate new v
		calculateV();
}

void calculateF() {
	calculation->calculateForce();
}


void calculateX() {
	calculation->calculatePosition();
}


void calculateV() {
	calculation->calculateVelocity();
}*/
