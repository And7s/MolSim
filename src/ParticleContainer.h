/*
 * ParticleContainer.h
 *
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */

#include <sstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>

#include "Particle.h"

using namespace std;

class ParticleContainer {

	private:
		std::list<Particle> particles;
		list<Particle>::iterator act_particle;
		list<Particle>::iterator inner_particle;

	public:
		ParticleContainer();
		ParticleContainer(std::list<Particle>& particles);
		~ParticleContainer();
		void setParticles(std::list<Particle>& particles);
		std::list<Particle>& getParticles();
		void resetIterator();
		void resetInnerIterator();
		bool isFinished(int i);
		void nextParticle(list<Particle>::iterator particle);
		void nextParticlePair();
		list<Particle>::iterator getActParticle();
		void setActParticle(list<Particle>::iterator actParticle);
		list<Particle>::iterator getInnerParticle();
		void setInnerParticle(list<Particle>::iterator innerParticle);

};
