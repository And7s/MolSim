/*
 * ParticleGenerator.h
 *
 *  Created on: Nov 7, 2013
 *      Author: friedrich
 */

#ifndef PARTICLEGENERATOR_H_
#define PARTICLEGENERATOR_H_

#include "Particle.h"
#include <list>
/*
 *
 */
class ParticleGenerator {
private:
	std::list<Particle> particleList;

public:
	ParticleGenerator();
	virtual ~ParticleGenerator();
};

#endif /* PARTICLEGENERATOR_H_ */
