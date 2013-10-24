
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


int main(int argc, char* argsv[]) {

	cout << "Hello from MolSim for PSE!" << endl;
	cout << "BlaTest" << endl;
	if (argc != 2) {
		cout << "Errounous programme call! " << endl;
		cout << "./molsym filename" << endl;
	}

	FileReader fileReader;
	fileReader.readFile(particles, argsv[1]);
	// the forces are needed to calculate x, but are not given in the input file.
	calculateF();

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
		}
		cout << "Iteration " << iteration << " finished." << endl;

		current_time += delta_t;
	}

	cout << "output written. Terminating..." << endl;
	return 0;
}


void calculateF() {
	list<Particle>::iterator iterator;
	iterator = particles.begin();

	while (iterator != particles.end()) {
		list<Particle>::iterator innerIterator = particles.begin();

		while (innerIterator != particles.end()) {
			if (innerIterator != iterator) {

				Particle& p1 = *iterator;
				Particle& p2 = *innerIterator;

				double scalar = ((p1.getM()*p2.getM())/((p1.getX()-p2.getX()).L2Norm()));
				p1.setOldF(p1.getF());
				p1.setF((p1.getX()-p2.getX())*scalar);
				// insert calculation of force here!

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
		
		p.setX(p.getX()+p.getV()*delta_t+delta_t*delta_t/(2*p.getM())*(p.getF());

		++iterator;
	}
}


void calculateV() {
	list<Particle>::iterator iterator = particles.begin();
	while (iterator != particles.end()) {

		Particle& p = *iterator;

		// insert calculation of velocity here!

		p.setV(p.getV()+(delta_t/(2*p.getM()))*(p.getOldF()+p.getF()));

		++iterator;
	}
}


void plotParticles(int iteration) {

	string out_name("MD_vtk");

	outputWriter::XYZWriter writer;
	writer.plotParticles(particles, out_name, iteration);
}
