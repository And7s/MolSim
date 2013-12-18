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
	LOG4CXX_TRACE(loggerPC, "Init ParticleContainer at Position: " << pos);
	this->position = pos;
	np = 0;
	npp1 = 0;
	npp2 = 1;
}

ParticleContainer::~ParticleContainer() {}

std::vector<Particle*> ParticleContainer::getParticles(){
	return particles;
}

void ParticleContainer::setParticles(std::vector<Particle*> particles) {
	this->particles = particles;
}

void ParticleContainer::setParticle(Particle* particle) {
	if(particle->getX()[2] != 0) {
		std::cerr<<"tryied to set unewual zero";
		exit(0);
	}
	this->particles.push_back(particle);
}


void ParticleContainer::deleteParticle(Particle* particle, bool destroy) {
	int i;
	int currentSize = this->particles.size();
	for(i=0; i < currentSize; i++){
		if((this->particles[i]->getX()[0] == particle->getX()[0]) &&
				(this->particles[i]->getX()[1] == particle->getX()[1]) &&
				(this->particles[i]->getX()[0] == particle->getX()[0])){
			break;
		}
	}
	if(i >= currentSize){
		return;
	}
	this->particles.erase(particles.begin()+i);
	if(destroy){
		delete particle;
		particle = NULL;
	}
}

void ParticleContainer::clearParticles() {
	this->particles.clear();
}

void ParticleContainer::show() {
	for(int i = 0; i < this->particles.size(); i++) {
		LOG4CXX_INFO(loggerPC, "PC (pos: " << this->position << ") " << i << " | " << particles[i]->toString());
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

Particle* ParticleContainer::nextParticle(int* iterator) {
	if((*iterator) >=this->particles.size()){
		*iterator = 0;
		return NULL;
	}
	(*iterator)++;
	return (particles[(*iterator)-1]);
}
