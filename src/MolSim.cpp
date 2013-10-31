
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

/*
 * values can be set at startup by passing params
 */
double start_time = 0;
double end_time = 1000; 
double delta_t = 0.014;

/*
 * stores the particles. accessed from Calculation by an external reference
 */
std::list<Particle> particles; 

/*
 * set algorithm, which should be used for the calculation.
 * The strategy pattern guarantees, that all spcial implementations are able to compute the requested values.
 */
Calculation *algorithm = new Sheet1Calc();

/*
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
	// the forces are needed to calculate x, but are not given in the input file.

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
		// calculate new x
		calculateX();
		// calculate new f
		calculateF();
		// calculate new v
		calculateV();
		//algorithm->calcAll();

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
	/*
	list<Particle>::iterator iterator;
			iterator = particles.begin();

			for (iterator = particles.begin(); iterator != particles.end();++iterator){
					Particle& p = *iterator;
					p.setOldF(p.getF());
					p.setF(utils::Vector<double, 3> (0.0));
			}

			iterator = particles.begin();

			while (iterator != particles.end()) {
				list<Particle>::iterator innerIterator = iterator;
				++innerIterator;

				while (innerIterator != particles.end()) {
					if (innerIterator != iterator) { 

						Particle& p1 = *iterator;
						Particle& p2 = *innerIterator;
						// insert calculation of force here!
						double tmp = ((p1.getX().operator -(p2.getX())).L2Norm());
						double tmp2 = std::pow(tmp,3);
						double tmp3 = (p1.getM()*p2.getM());
						double scalar = tmp3/tmp2;

						utils::Vector<double, 3> forceIJ = (p2.getX().operator-(p1.getX())).operator*(scalar);
						p1.addOnF(forceIJ);
						p2.addOnF(forceIJ*(-1));
					}
					++innerIterator;
				}
				++iterator;
			}
			*/
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
