#include "ParticleContainer.h"
#include "Particle.h"
#include "utils/Vector.h"

#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include <sstream>
#include <iostream>
#include <list>
#include <cstring>
#include <cstdlib>

using namespace std;

ParticleContainer::ParticleContainer(std::list<Particle> particles, double start_time, double end_time, double delta_t) {
	this->start_time = start_time;
	this->end_time = end_time;
	this->delta_t = delta_t;
	this->particles = particles;
	innerpos = 0;
}

bool ParticleContainer::getNextPair(Particle *p1, Particle *p2) {
	
	/*
		
	if(nextPP1 != particles.end()) {
		if(nextPP2 != particles.end()) {
			//good
		}else {

			nextPP1++;
			innerpos++;
			nextPP2 = particles.begin();
			for(int i = 0; i <= innerpos; i++) {
				nextPP2++;
			}
			
			if(nextPP1 != particles.end() && nextPP2 != particles.end()) {
				//good too
			}else {
				nextPP1 = particles.begin();
				nextPP2 = particles.begin();
				nextPP2++;
				return false;
			}
		}
		Particle& tp1 = *nextPP1;
		p1 = &tp1;

		Particle& tp2 = *nextPP2;
		p2 = &tp2;

		nextPP2++;
		return true;

	}else {
		nextPP1 = particles.begin();
		nextPP2 = particles.begin();
		nextPP2++;
		return false;
	}*/
	
}



bool ParticleContainer::getNextParticle(Particle *p) {
	
	if(nextP != particles.end()) {
		Particle& p1 = *nextP;
		p = &p1;
		nextP++;
		return true;
	}else {
		cout << "end";
		nextP = particles.begin();
		return false;
	}


}
void ParticleContainer::calculate() {
	double current_time = start_time;

	int iteration = 0;
	calculateF();
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
}

void ParticleContainer::plotParticles(int iteration) {
	outputWriter::VTKWriter writer;
	writer.initializeOutput(4);
	string out_name("MD_vtk");
	
	list<Particle>::iterator iterator;
	iterator = particles.begin();
	int i = 0;
	while (iterator != particles.end()) {
		Particle& p1 = *iterator;
		writer.plotParticle(p1);
		++iterator;
		i++;
		cout << "P" << i << ": " << p1.toString() << endl;
	}
	writer.writeFile("vtk", iteration);
}


void ParticleContainer::calculateX() {
	Particle* p;
	while (getNextParticle(p)) {
		utils::Vector<double, 3> part1 = p->getX();
		utils::Vector<double, 3> part2 = p->getV().operator*(delta_t);
		double scalar = delta_t*delta_t/(2*p->getM());
		utils::Vector<double, 3> part3 = p->getF() * (scalar);
		utils::Vector<double, 3> newX = part1.operator +(part2.operator +(part3));
		p->setX(newX);		
	}
}

void ParticleContainer::calculateV() {
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

void ParticleContainer::calculateF() {
	/*list<Particle>::iterator iterator;
	iterator = particles.begin();
*/
	/*for (iterator = particles.begin(); iterator != particles.end();++iterator){
			Particle& p = *iterator;
			p.setOldF(p.getF());
			p.setF(utils::Vector<double, 3> (0.0));
	}*/

	/*	Particle *p1;
		Particle *p2;
		while(getNextPair(p1, p2)){
			double tmp = ((p1->getX().operator -(p2->getX())).L2Norm());
			double tmp2 = std::pow(tmp,3);
			double tmp3 = (p1->getM()*p2->getM());
			double scalar = tmp3/tmp2;

			utils::Vector<double, 3> forceIJ = (p1->getX().operator-(p2->getX())).operator*(scalar);
			p1->addOnF(forceIJ*(-1));
		}
*/
/*
	iterator = particles.begin();

	while (iterator != particles.end()) {
		list<Particle>::iterator innerIterator = particles.begin();

		while (innerIterator != particles.end()) {
			if (innerIterator != iterator) {

				Particle& p1 = *iterator;
				Particle& p2 = *innerIterator;
				// insert calculation of force here!
				double tmp = ((p1.getX().operator -(p2.getX())).L2Norm());
				double tmp2 = std::pow(tmp,3);
				double tmp3 = (p1.getM()*p2.getM());
				double scalar = tmp3/tmp2;

				utils::Vector<double, 3> forceIJ = (p1.getX().operator-(p2.getX())).operator*(scalar);
				p1.addOnF(forceIJ*(-1));
			}
			++innerIterator;
		}
		++iterator;
	}*/
}