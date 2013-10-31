/*
 * ParticleContainer.cpp
 *
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include "ParticleContainer.h"
#include "Particle.h"
#include "utils/Vector.h"

#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include <sstream>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

/**
 * references to particle list in MolSim.cpp
 */
extern std::list<Particle> particles;

/**
 * calls a function for a certain particle
 */
void ParticleContainer::perParticle(std::function<void (Particle&)> fn){
	std::list<Particle>::iterator iterator = particles.begin();
	for(;iterator != particles.end();iterator++){
		fn(*iterator);
	}
}

/**
 * calls a function for a certain pair of particles
 */
void ParticleContainer::pairOfParticles(std::function<void (Particle&, Particle&)> fn) {
        std::list<Particle>::iterator iterator;
        iterator = particles.begin();

        while (iterator != particles.end()) {
                std::list<Particle>::iterator innerIterator = particles.begin();
                while (innerIterator != particles.end()) {
                        if (innerIterator != iterator) {
						fn(*iterator, *innerIterator);
                        }
                        ++innerIterator;
                }
                ++iterator;
        }
}

/**
 * returns a list of all particles
 */
std::list<Particle> ParticleContainer::getParticles(){
	return particles;
}



