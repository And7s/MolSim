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
		Particle**& getParticles();
		void show();
		Particle* nextParticlePair1();
		Particle* nextParticlePair2();
		Particle* nextParticle();
		int getLength();
		void setLength(int length);
		int getNp();
		void setNp(int np);
		int getNpp1();
		void setNpp1(int npp1);
		int getNpp2();
		void setNpp2(int npp2);
};

#endif /* PARTICLECONTAINER_H_ */