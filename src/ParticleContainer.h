/*
 * ParticleContainer.h
 *
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */

#ifndef PARTICLECONTAINER_H_
#define PARTICLECONTAINER_H_

#include <sstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>

#include "Particle.h"
using namespace std;
/**
 * ParticleContainer which contains the list of particles
 */
class ParticleContainer {
	protected:
		Particle** particles;
		int np, npp1, npp2;
		int length;
	public:
		ParticleContainer();
		ParticleContainer(int l);
		~ParticleContainer();
		void setParticles(std::list<Particle>& particles);
		void show();
		Particle* nextParticlePair1();
		Particle* nextParticlePair2();
		Particle* nextParticle();
		

};

#endif /* PARTICLECONTAINER_H_ */
