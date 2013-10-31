
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

extern std::list<Particle> particles;

void ParticleContainer::perParticle(std::function<void (Particle&)> fn){
	std::list<Particle>::iterator iterator = particles.begin();
	for(;iterator != particles.end();iterator++){
		fn(*iterator);
	}
}

void ParticleContainer::pairOfParticles(std::function<void (Particle&, Particle&)> fn) {
		//cout << "in pairOfParticles" << endl;
        std::list<Particle>::iterator iterator;
        iterator = particles.begin();

        while (iterator != particles.end()) {
                std::list<Particle>::iterator innerIterator = particles.begin();
				//cout << "in pairOfParticles first while" << endl;
                while (innerIterator != particles.end()) {
                        if (innerIterator != iterator) {
						fn(*iterator, *innerIterator);
                        }
                        ++innerIterator;
                }
                ++iterator;
        }
}

std::list<Particle> ParticleContainer::getParticles(){
	return particles;
}



