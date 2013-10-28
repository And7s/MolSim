
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "FileReader.h"

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

outputWriter::VTKWriter writer;

int main(int argc, char* argsv[]) {

	writer.initializeOutput(4);

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
	// the forces are needed to calculate x, but are not given in the input file.
	cout << "Initializing forces: " << endl;
	calculateF();
	cout << "Forces initialized." << endl;

	double current_time = start_time;

	int iteration = 0;

	 // for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {
		//cout << "Calculation. Iteration: " << iteration << endl;
		// calculate new x
		calculateX();
		// calculate new f
		calculateF();
		// calculate new v
		calculateV();

		iteration++;
		if (iteration % 10 == 0) {
			plotParticles(iteration);
		}
		cout << "Iteration " << iteration << " finished." << endl;

		current_time += delta_t;
	}
	writer.writeFile("vtk", iteration);
	cout << "output written. Terminating..." << endl;
	return 0;
}


void calculateF() {
	list<Particle>::iterator iterator;
	iterator = particles.begin();

	for (iterator = particles.begin(); iterator != particles.end();++iterator){
			Particle& p = *iterator;
			p.setOldF(p.getF());
			p.setF(utils::Vector<double, 3> (0.0));
	}

	iterator = particles.begin();

	while (iterator != particles.end()) {
		list<Particle>::iterator innerIterator = particles.begin();

		while (innerIterator != particles.end()) {
			if (innerIterator != iterator) {

				Particle& p1 = *iterator;
				Particle& p2 = *innerIterator;
				// insert calculation of force here!
				//cout << "Force calculation: p1 before calculation: " << p1.toString() << endl;
				double tmp = ((p1.getX().operator -(p2.getX())).L2Norm());
				double tmp2 = std::pow(tmp,3);
				double tmp3 = (p1.getM()*p2.getM());
				double scalar = tmp3/tmp2;
				//p1.setOldF(p1.getF());
				utils::Vector<double, 3> forceIJ = (p1.getX().operator-(p2.getX())).operator*(scalar);
				p1.addOnF(forceIJ);

				//cout << "Force calculation: p1 after calculation: " << p1.toString() << endl;

			}
			++innerIterator;
		}
		++iterator;
	}
}


void calculateX() {
	list<Particle>::iterator iterator = particles.begin();
	while (iterator != particles.end()) {

		Particle& p = *iterator;
		utils::Vector<double, 3> part1 = p.getX();
		utils::Vector<double, 3> part2 = p.getV().operator*(delta_t);
		double scalar = delta_t*delta_t/(2*p.getM());
		utils::Vector<double, 3> part3 = p.getF().operator*(scalar);
		utils::Vector<double, 3> newX = part1.operator +(part2.operator +(part3));
		p.setX(newX);

		++iterator;
	}
}


void calculateV() {
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

	string out_name("MD_vtk");

	
	
	list<Particle>::iterator iterator;
	iterator = particles.begin();
	while (iterator != particles.end()) {
		Particle& p1 = *iterator;
		writer.plotParticle(p1);
		++iterator;
	}
}
