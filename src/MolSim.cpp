
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "FileReader.h"
#include "Calculation.cpp"
#include "Plotter.cpp"

#include <list>
#include <cstring>
#include <cstdlib>
#include <iostream>

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
 * plot the particles to a xyz-file
 */
void plotParticles(int iteration); 


double start_time = 0;
double end_time = 1000; 
double delta_t = 0.014;

std::list<Particle> particles;

Calculation *algorithm = new Sheet1Calc();
Plotter *vtkPlotter = new VTK();

int main(int argc, char* argsv[]) {

	cout << "Hello from MolSim for PSE!" << endl;
	if (argc != 4) {
		cout << "Errounous programme call! " << endl;
		cout << "./molsym filename" << endl;
		exit(-1);
	}

	end_time = atof(argsv[2]);
	delta_t = atof(argsv[3]);

	FileReader fileReader;
	fileReader.readFile(particles, argsv[1]);
	
	
	ParticleContainer* pc;
	//pc->setParticles(particles);
	//algorithm->setParticles(particles);
	algorithm->setParticleContainer(pc);
	algorithm->setDeltaT(delta_t);

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
			vtkPlotter->plotParticles(iteration);
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
	algorithm->calculateForce();
}


void calculateX() {
	//algorithm->calculatePosition();
	
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
	}
}


void calculateV() {
	//algorithm->calculateVelocity();
	
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
	
}
