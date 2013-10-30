
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

ParticleContainer::ParticleContainer(std::list<Particle> particles) {
	this->particles = particles;
	innerpos = 0;
}

bool ParticleContainer::getNextPair(Particle *p1, Particle *p2) {
	
	/*
		
	if(nextPP1 != particles.end()) {
		if(nextPP2 != particles.end()) {
			//good
		}else {

			nextPP1++;
			innerpos++;
			nextPP2 = particles.begin();
			for(int i = 0; i <= innerpos; i++) {
				nextPP2++;
			}
			
			if(nextPP1 != particles.end() && nextPP2 != particles.end()) {
				//good too
			}else {
				nextPP1 = particles.begin();
				nextPP2 = particles.begin();
				nextPP2++;
				return false;
			}
		}
		Particle& tp1 = *nextPP1;
		p1 = &tp1;

		Particle& tp2 = *nextPP2;
		p2 = &tp2;

		nextPP2++;
		return true;

	}else {
		nextPP1 = particles.begin();
		nextPP2 = particles.begin();
		nextPP2++;
		return false;
	}*/
	
}



bool ParticleContainer::getNextParticle(Particle *p) {
	
	if(nextP != particles.end()) {
		Particle& p1 = *nextP;
		p = &p1;
		nextP++;
		return true;
	}else {
		cout << "end";
		nextP = particles.begin();
		return false;
	}


}


