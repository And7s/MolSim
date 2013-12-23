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
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "Particle.h"

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;


/**
 * ParticleContainer which contains the list of particles
 */
class ParticleContainer {
	protected:
		std::vector<Particle*> particles;
		int np, npp1, npp2;
		int position;
	public:
		ParticleContainer();
		ParticleContainer(int l);
		~ParticleContainer();
		std::vector<Particle*> getParticles();

		void setParticles(std::vector<Particle*> particles);

		/**
		 * adds a single particle to the container
		 */
		void setParticle(Particle* particle);

		/**
		 * @param particle
		 * @param destroy true, to delete from RAM
		 */
		void deleteParticle(Particle* particle, bool destroy);

		/**
		 * this is less precise than deleteParticle(), since this deletes the whole vector, but more effective.
		 */
		void clearParticles();

		/**
		 * prints the particles of this particleContainer
		 */
		void show();

		/**
		 * Returns a pointer to the outerParticle of a pair
		 * @return Particle*
		 */
		Particle* nextParticlePair1();

		/**
		 * Returns a pointer to the innerParticle of a pair
		 * @return Particle*
		 */
		Particle* nextParticlePair2();

		/**
		 * Returns a Pointer to the next Particle
		 * @return Particle*
		 */
		Particle* nextParticle();

		/**
		 * Returns a Pointer to the Particle at the specific position iterator
		 * @param iterator
		 * @return Particle*
		 */
		inline Particle* nextParticle(int* iterator);

		int getLength();
		int getNp();
		void setNp(int np);
		int getNpp1();
		void setNpp1(int npp1);
		int getNpp2();
		void setNpp2(int npp2);
		int getPosition();
};

Particle* ParticleContainer::nextParticle(int* iterator) {
	if((*iterator) >=this->particles.size()){
		*iterator = 0;		
		return NULL;
	}
	(*iterator)++;
	return (particles[(*iterator)-1]);
}



#endif /* PARTICLECONTAINER_H_ */
