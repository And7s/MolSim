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
		std::list<Particle> particles;
		list<Particle>::iterator act_particle;
		list<Particle>::iterator inner_particle;

	public:
		ParticleContainer();
		ParticleContainer(std::list<Particle>& particles);
		~ParticleContainer();

		/**
		 * Set particlelist in particlecontainer
		 * @param particles
		 */
		void setParticles(std::list<Particle>& particles);

		/**
		 * get reference to particlelist
		 * @return std::list<Particle>&
		 */
		std::list<Particle>& getParticles();

		/**
		 * reset Iterator act_particle of particellist to the beginning of the list
		 */
		void resetIterator();

		/**
		 * reset second Iterator inner_particle of particlelist to the beginning of the list
		 * needed of inner loops
		 */
		void resetInnerIterator();

		/**
		 * Returns boolean if you are at the end of the list
		 * @param i
		 * = 0 for act_particle Iterator, = 1 for inner_particle Iterator
		 * @return bool
		 */
		bool isFinished(int i);

		/**
		 * Increases particle Iterator by one
		 * @param particle
		 */
		void nextParticle(list<Particle>::iterator particle);

		/**
		 * TODO not implemented/used yet
		 */
		void nextParticlePair();
		
		/**
		 * returns act_particle iterator
		 * @return list<Particle>::iterator
		 */
		list<Particle>::iterator getActParticle();

		/**
		 * sets act_particle iterator
		 * @param actParticle
		 */
		void setActParticle(list<Particle>::iterator actParticle);
		/**
		 * returns inner_particle iterator
		 * @return list<Particle>::iterator
		 */
		list<Particle>::iterator getInnerParticle();

		/**
		 * sets inner_particle iterator
		 * @param innerParticle
		 */
		void setInnerParticle(list<Particle>::iterator innerParticle);

};

#endif /* PARTICLECONTAINER_H_ */
