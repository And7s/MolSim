//particlegenerator.h

#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include "Particle.h"


class ParticleGenerator {
private:

public:
	ParticleGenerator();
	~ParticleGenerator();
	Particle** readFile(char* filename);
};

#endif