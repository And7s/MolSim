/*
 * EnvironmentalInfluences.h
 *
 *  Created on: Dec 8, 2013
 *      Author: paul
 */

#ifndef ENVINFL_H_
#define ENVINFL_H_

#include "Particle.h"
#include "SpecializedParticle.h"

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/**
 * this class provides general environmental influences on the particles. Most likely, those forces do not depend on the location of the particle,
 * since they affect the whole space evenly.
 * Forces like gravity, wind, vortexes etc may defined here.
 * The class should only exist once, but reachable from anywhere, so it is a singleton.
 */
class EnvInfl {
private:
	/**
	 * singleton
	 */
	EnvInfl();
	virtual ~EnvInfl();

	/**
	 * instance
	 */
	static EnvInfl* instance;

public:
	std::vector<SpecializedParticle*> specParts;

	static EnvInfl* getInstance();

	static void destroy();

	/**
	 * gravity acceleration
	 */
	double g;

	/**
	 * set the gravity acceleration
	 */
	void setG(double g);

	/**
	 * get the gravity acceleration
	 */
	double getG();

	void calculateGravity(Particle* parts);

	void calculateSpecParts(int timestep);

	/**
	 * setup the particles special list
	 */
	void addSpecPart(double startTime, double endTime, std::vector<double> force, bool relative, Particle* part);

};

#endif /* ENVINFL */
