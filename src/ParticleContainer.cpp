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

ParticleContainer::ParticleContainer() {
	//std::cout << "new ParticleContainer";
}

ParticleContainer::ParticleContainer(int pos) {
	LOG4CXX_TRACE(loggerPC, "Init ParticleContainer at Position: " << pos);
	this->position = pos;
	operatingThread = -1;
}

ParticleContainer::~ParticleContainer() {}

std::vector<Particle*> ParticleContainer::getParticles(){
	return particles;
}

void ParticleContainer::setParticles(std::vector<Particle*> particles) {
	this->particles = particles;
}

void ParticleContainer::setParticle(Particle* particle) {
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


int ParticleContainer::getLength() {
	return this->particles.size();
}


int ParticleContainer::getPosition(){
	return this->position;
}

void ParticleContainer::setOperatingThread(int threadNum) {
	if(operatingThread == -1 || threadNum == this->operatingThread){
		this->operatingThread = threadNum;
	}else{
		LOG4CXX_WARN(loggerPC, "Particle Container at position: " <<this->position << " has changed operating thread from " << this->operatingThread << " to " <<threadNum);
	}
}
