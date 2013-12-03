/*
 * ParticleContainer.cpp
 * Stores the particles in an array. For calculation the particles can be accessed single or pair wise.
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include "ParticleContainer.h"
#include "Particle.h"

/**
 * Logger
 */
LoggerPtr loggerPC(Logger::getLogger( "main.pc"));

ParticleContainer::ParticleContainer() {}
ParticleContainer::ParticleContainer(int pos) {
	//LOG4CXX_TRACE(loggerPC, "Init ParticleContainer of length: " << length);
	//particles = new Particle*[length];
	this->position = pos;
	np = 0;
	npp1 = 0;
	npp2 = 1;
}

ParticleContainer::~ParticleContainer() {}

/*
void ParticleContainer::setParticles(Particle** particles_) {
	particles = particles_;
}

Particle**& ParticleContainer::getParticles() {
	return particles;
}
*/
std::vector<Particle*> ParticleContainer::getParticles(){
	return particles;
}

void ParticleContainer::setParticles(std::vector<Particle*> particles) {
	this->particles = particles;
}

void ParticleContainer::setParticle(Particle* particle) {
	this->particles.push_back(particle);
}

void ParticleContainer::show() {
	for(int i = 0; i < this->particles.size(); i++) {
		LOG4CXX_TRACE(loggerPC, "P " << i << " | " << particles[i]);
	}
}

Particle* ParticleContainer::nextParticlePair1() {
	if(npp1 == this->particles.size()) {
		npp1 = 0;
		npp2 = npp1+1;
		return NULL;
	}else {
		npp1++;
		return (particles[npp1-1]);
	}
}

Particle* ParticleContainer::nextParticlePair2() {
	if(npp2 >= this->particles.size()) {
		npp2 = npp1+1;
		return NULL;
	}else {
		npp2++;
		return (particles[npp2-1]);
	}
}

int ParticleContainer::getLength() {
	return this->particles.size();
}

int ParticleContainer::getNp() {
	return np;
}

void ParticleContainer::setNp(int np) {
	this->np = np;
}

int ParticleContainer::getNpp1() {
	return npp1;
}

void ParticleContainer::setNpp1(int npp1) {
	this->npp1 = npp1;
}

int ParticleContainer::getNpp2() {
	return npp2;
}

void ParticleContainer::setNpp2(int npp2) {
	this->npp2 = npp2;
}

int ParticleContainer::getPosition(){
	return this->position;
}

Particle* ParticleContainer::nextParticle() {
	if(np == this->particles.size()) {
		np = 0;
		return NULL;
	}else {
		np++;
		return (particles[np-1]);
	}
}


