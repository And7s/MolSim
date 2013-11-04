/*
 * ParticleContainer.cpp
 *
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include "ParticleContainer.h"
#include "Particle.h"

ParticleContainer::ParticleContainer() {}
ParticleContainer::ParticleContainer(int l) {
	length = l;
	cout << "init pc";
	particles = new Particle*[length];
	np = 0;
	npp1 = 0;
	npp2 = 1;
}
ParticleContainer::~ParticleContainer() {}


void ParticleContainer::setParticles(std::list<Particle>& p) {
	int j = 0;
	for(list<Particle>::iterator i = p.begin(); i != p.end() && j < length; i++) {
		cout << "Assign particle";
		particles[j] = &(*i);
		j++;
	}
	show();
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

Particle* ParticleContainer::nextParticle() {
	if(np == length) {
		np = 0;
		return NULL;
	}else {
		np++;
		return particles[np-1];	
	}
}


