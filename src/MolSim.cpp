
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "FileReader.h"
#include "Calculation.cpp"

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
 * plot the particles to a xyz-file
 */
void plotParticles(int iteration); 


double start_time = 0;
double end_time = 1000; 
double delta_t = 0.014;

std::list<Particle> particles;

Calculation *algorithm = new Sheet1Calc();
ParticleContainer *pc = new ParticleContainer(particles);

int main(int argc, char* argsv[]) {

	cout << "Hello from MolSim for PSE!" << endl;
	if (argc != 4) {
		cout << "Errounous programme call! " << endl;
		cout << "./molsym filename" << endl;
		exit(-1);
	}

	end_time = atof(argsv[2]);
	delta_t = atof(argsv[3]);

	algorithm->setParticleContainer(pc);
	algorithm->setDeltaT(delta_t);

	FileReader fileReader;
	fileReader.readFile(particles, argsv[1]);
	// the forces are needed to calculate x, but are not given in the input file.
	cout << "Initializing forces: " << endl;
	calculateF();
	cout << "Forces initialized." << endl;

	double current_time = start_time;

	int iteration = 0;

	 // for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {

		
		// calculate new x
		calculateX();
		// calculate new f
		calculateF();
		// calculate new v
		calculateV();

		iteration++;
		if (iteration % 10 == 0) {
			plotParticles(iteration);
			cout << "Iteration " << iteration << " finished." << endl;
		}
		

		current_time += delta_t;

	}

	cout << "output written. Terminating..." << endl;
	return 0;
}


void calculateF() {
	algorithm->calculateForce();
}


void calculateX() {
	algorithm->calculatePosition();
	/*list<Particle>::iterator iterator = particles.begin();
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
	algorithm->calculateVelocity();
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


void plotParticles(int iteration) {
	outputWriter::VTKWriter writer;
	writer.initializeOutput(4);
	
	list<Particle>::iterator iterator;
	iterator = particles.begin();
	int i = 0;
	while (iterator != particles.end()) {
		Particle& p1 = *iterator;
		writer.plotParticle(p1);
		++iterator;
		i++;
		//cout << "P" << i << ": " << p1.toString() << endl;
	}
	writer.writeFile("vtk", iteration);
}
