/*
 * ParticleContainer.cpp
 *
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include "ParticleContainer.h"

ParticleContainer::ParticleContainer() {
}

ParticleContainer::~ParticleContainer() {
}

ParticleContainer::ParticleContainer(std::list<Particle>& particles) {
	this->particles = particles;
	act_particle = particles.begin();
}

void ParticleContainer::setParticles(std::list<Particle>& particles) {
	this->particles = particles;
}

std::list<Particle>& ParticleContainer::getParticles() {
	return particles;
}


void ParticleContainer::resetIterator() {
	act_particle = particles.begin();
}

bool ParticleContainer::isFinished(int i) {
	if(i!=0 && i!=1){
		cout << "Wrong Input in ParticleContainer.isFinished(): i = " << i << endl;
		cout << "Should be 0 or 1" << endl;
		exit(1);
	}
	if(i==0){
		return (act_particle == particles.end());
	}else{
		return (inner_particle == particles.end());
	}
}

void ParticleContainer::nextParticle(list<Particle>::iterator particle) {
	particle++;
}

list<Particle>::iterator ParticleContainer::getActParticle(){
	return act_particle;
}

void ParticleContainer::setActParticle(list<Particle>::iterator actParticle) {
	act_particle = actParticle;
}

list<Particle>::iterator ParticleContainer::getInnerParticle(){
	return inner_particle;
}

void ParticleContainer::setInnerParticle(
	list<Particle>::iterator innerParticle) {
	inner_particle = innerParticle;
}

void ParticleContainer::nextParticlePair() {
}
