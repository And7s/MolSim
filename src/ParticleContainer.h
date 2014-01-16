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

		int position;

		/**
		 * the number of the operating Thread on this PC
		 * more likely for development purpose.
		 */
		int operatingThread;
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
		 * Returns a Pointer to the Particle at the specific position iterator
		 * @param iterator
		 * @return Particle*
		 */
		inline Particle* nextParticle(int* iterator);

		int getLength();

		int getPosition();

		inline bool isempty();

		void setOperatingThread(int threadNum);
};

Particle* ParticleContainer::nextParticle(int* iterator) {
	if((*iterator) >=this->particles.size()){
		*iterator = 0;		
		return NULL;
	}
	(*iterator)++;
	return (particles[(*iterator)-1]);
}

bool ParticleContainer::isempty() {
	return this->particles.size() == 0;
}

#endif /* PARTICLECONTAINER_H_ */
