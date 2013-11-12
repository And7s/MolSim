//particlegenerator.h

#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include "Particle.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

class ParticleGenerator {
private:

public:
	ParticleGenerator();
	~ParticleGenerator();
	Particle** readFile(char* filename, int* length);
};

#endif
