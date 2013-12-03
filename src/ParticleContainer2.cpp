/*
 * ParticleContainer2.cpp
 *
 *  Created on: Dec 1, 2013
 *      Author: friedrich
 */

#include "ParticleContainer2.h"

ParticleContainer2::ParticleContainer2() {
	// TODO Auto-generated constructor stub

}

ParticleContainer2::~ParticleContainer2() {
	// TODO Auto-generated destructor stub
}

std::list<Particle>*& ParticleContainer2::getParticles(){
	return particles;
}

void ParticleContainer2::setParticles(std::list<Particle>*& particles) {
	this->particles = particles;
	outerIterator = this->particles->begin();
	innerIterator = outerIterator++;
}

std::pair<Particle&, Particle&> ParticleContainer2::getNextPair() {
	if(outerIterator==--(particles->end())){
		return ParticlePair(*outerIterator,*outerIterator);
	}else{
		if(innerIterator==particles->end()){
			outerIterator++;
			innerIterator = outerIterator++;
			return ParticlePair(*outerIterator,*innerIterator);
		}
		innerIterator++;
		return ParticlePair(*outerIterator,*innerIterator);
	}
}

Particle* ParticleContainer2::getNextParticle() {
	if(outerIterator==(particles->end())){
		outerIterator==particles->begin();
		return NULL;
	}else{
		std::list<Particle>::iterator previousIterator = outerIterator;
		outerIterator++;
		Particle* p = &*previousIterator;
		return p;
	}
}
