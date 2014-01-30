#ifndef CALCULATION_H_
#define CALCULATION_H_

#include "ParticleContainer.h"
#include "LCDomain.h"
#include "EnvInfl.h"
#include "Particle.h"
#include "DynamicThreadMngr.h"

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include <math.h>
#include <omp.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/**
 * Interface for Calculation
 */
class Calculation {

protected:
	LCDomain* lcDomain;
	ParticleContainer particleContainer;
	double delta_t;


public:
	virtual ~Calculation() {
	}

	/**
	 * Function to calculate the position
	 */
	void calculatePosition();

	/**
	 * Function to calculate the velocity
	 */
	void calculateVelocity();

	/**
	 * Function which chooses the right strategy to calculate the force between two particles
	 */
	void calculateForce(double currentTime);

	/**
	 * Function to calculate velocity, position and force at once
	 */
	void calculateAll(double currentTime);

	/**
	 * Function to reset the force of all particles to zero
	 */
	void resetForce();

	/**
	 * Function to calculate the force between the two specific particles p1 and p2
	 * @param p1
	 * @param p2
	 */
	static void calculateSingleForce(Particle* p1, Particle* p2);

	/**
	 * Function to calculate the LennardJonesInteraction for Particle p between Particle p and Particle curP
	 * @param p
	 * @param curP
	 * @param length
	 * @param cutOff
	 */
	static void calculateLJInteraction(Particle* p, Particle* curP, double length, double cutOff);

	/**
	 * Function to calculate the MembraneInteraction for Particle p between Particle p and Particle curP
	 * @param p
	 * @param curP
	 * @param length
	 * @param cutOff
	 * @param sidelength
	 * @param k
	 * @param r0
	 * @param r0sqrt
	 * @param mindist
	 */
	static void calculateMembraneInteraction(Particle* p, Particle* curP, double length, double cutOff, int sidelength, double k, double r0, double r0sqrt, double mindist);

	void setParticleContainer(ParticleContainer& pc_);

	ParticleContainer& getParticleContainer();

	void setDeltaT(double deltaT);

	double getDeltaT();

	void setLcDomain(LCDomain* lcDomain);

	LCDomain* getLcDomain();

	int counterAll, counterMiss;
};






#endif /* CALCULATION_H_ */
