/*
 * ParticleContainer.cpp
 * Stores the particles in an array. For calculation the particles can be accessed single or pair wise.
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include "ParticleContainer.h"
#include "Particle.h"

ParticleContainer::ParticleContainer() {}
ParticleContainer::ParticleContainer(int l) {
	length = l;
	cout << "init ParticleContainer of Length: "<<length<<endl;
	particles = new Particle*[length];
	np = 0;
	npp1 = 0;
	npp2 = 1;
}

ParticleContainer::~ParticleContainer() {}


void ParticleContainer::setParticles(Particle** particles_) {
	particles = particles_;
}

Particle**& ParticleContainer::getParticles() {
	return particles;
}

void ParticleContainer::show() {
	for(int i = 0; i < length; i++) {
		cout << "P" << i << *particles[i] << endl;
	}
}

Particle* ParticleContainer::nextParticlePair1() {
	if(npp1 == length) {
		npp1 = 0;
		npp2 = npp1+1;
		return NULL;
	}else {
		npp1++;
		return particles[npp1-1];
	}
}

Particle* ParticleContainer::nextParticlePair2() {
	if(npp2 >= length) {
		npp2 = npp1+1;
		return NULL;
	}else {
		npp2++;
		return particles[npp2-1];
	}
}

int ParticleContainer::getLength() {
	return length;
}

void ParticleContainer::setLength(int length) {
	this->length = length;
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

Particle* ParticleContainer::nextParticle() {
	if(np == length) {
		np = 0;
		return NULL;
	}else {
		np++;
		return particles[np-1];	
	}
}


