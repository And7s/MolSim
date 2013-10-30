#ifndef PARTICLE_COL_H_
#define PARTICLE_COL_H_

#include "Particle.h"
#include <list>


class ParticleCollection {
public:
	double x;
	std::list<Particle *> particles;
	std::list<Particle *>::iterator nextP;
	std::list<Particle *>::iterator nextPP1;
	std::list<Particle *>::iterator nextPP2;

	ParticleCollection(std::list<Particle> particles_);
	void Show();

	bool getNextParticle(Particle &p);
	bool getNextParticlePair(Particle &p1, Particle &p2);
};
#endif