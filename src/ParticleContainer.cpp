#include "Particle.h"

#include <iostream>
#include <vector>

using namespace std;


class ParticleContainer{
	public:

		
		bool getNextPair(Particle *p1, Particle *p2){
			Particle p;
			p1 = &p;
			p2 = &p;
			return true;
		}

		void getNextParticle(Particle *p1){
			Particle p;
			p1 = &p;
		}
};
