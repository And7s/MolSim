//particlegenerator.h

#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include "MaxwellBoltzmannDistribution.h"

#include "Particle.h"
#include "utils/Vector.h"
#include "help_macros.h"
#include "input.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

#include <memory>   // std::auto_ptr
#include <iostream>


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
	std::vector<Particle*> readFile(int* length, auto_ptr<input_t>& inp, int* uid);
};

#endif
