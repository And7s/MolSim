//particlegenerator.h

#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "Particle.h"
#include "utils/Vector.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace std;

class ParticleGenerator {
private:

public:
	ParticleGenerator();
	~ParticleGenerator();
	/**
	 * Reads the File filename and generates particles forming a cuboid
	 * @param filename
	 * @param length
	 * @return
	 */
	Particle** readFile(char* filename, int* length);
};

#endif
