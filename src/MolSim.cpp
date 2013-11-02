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

/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 */
void calculateF();

/**
 * calculate the position for all particles
 */
void calculateX(); 

/**
 * calculate the position for all particles 
 */
void calculateV(); 

/**
 * calculate the position, the force and velocity for all particles by using the above methods
 */
void calcAll();

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
Calculation *calculation = new Sheet1Calc();
Plotter *vtkPlotter = new VTK();

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
	
	ParticleContainer pc;
	calculation->setParticleContainer(pc);
	calculation->setDeltaT(delta_t);

	// the forces are needed to calculate x, but are not given in the input file.
	cout << "Initializing forces: " << endl;
	calculateF();
	cout << "Forces initialized." << endl;

	double current_time = start_time;

	int iteration = 0;

	 // for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {
		// calculate new x, new f, new v
		calcAll();

		iteration++;
		if (iteration % 10 == 0) {
			vtkPlotter->plotParticles(iteration, particles.size());
			cout << "Iteration " << iteration << " finished." << endl;
		}
		current_time += delta_t;
	}

	cout << "output written. Terminating..." << endl;
	return 0;
}

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
	/*
	list<Particle>::iterator iterator = particles.begin();
	while (iterator != particles.end()) {

		Particle& p = *iterator;
		utils::Vector<double, 3> part1 = p.getX();
		utils::Vector<double, 3> part2 = p.getV().operator*(delta_t);
		double scalar = delta_t*delta_t/(2*p.getM());
		utils::Vector<double, 3> part3 = p.getF() * (scalar);
		utils::Vector<double, 3> newX = part1.operator +(part2.operator +(part3));
		p.setX(newX);

		++iterator;
	}*/
}


void calculateV() {
	calculation->calculateVelocity();
	/*
	list<Particle>::iterator iterator = particles.begin(); 
	while (iterator != particles.end()) {

		Particle& p = *iterator;

		// insert calculation of velocity here!
		utils::Vector<double, 3> part1 = p.getV();
		double scalar = delta_t/(2*p.getM());
		utils::Vector<double, 3> part2 = (p.getOldF().operator+(p.getF())).operator *(scalar);
		utils::Vector<double, 3> newV = part1.operator +(part2);
		p.setV(newV);

		++iterator;
	}
	*/
}
