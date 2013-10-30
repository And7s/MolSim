#include <list>
#include "Particle.h"
#include <sstream>
#include <iostream>

class ParticleContainer {
	private:
		std::list<Particle> particles;

		std::list<Particle>::iterator nextP;
		std::list<Particle>::iterator nextPP1;
		std::list<Particle>::iterator nextPP2;

	public:
		ParticleContainer(std::list<Particle> particles);
		bool getNextPair(Particle *p1, Particle *p2);
		bool getNextParticle(Particle *p);
		int innerpos;
};
