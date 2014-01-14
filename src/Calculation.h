#ifndef CALCULATION_H_
#define CALCULATION_H_

#include "ParticleContainer.h"
#include "LCDomain.h"
#include "EnvInfl.h"
#include "Particle.h"

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
	 * function to calculate the position
	 */
	void calculatePosition();

	/**
	 * function to calculate the velocity
	 */
	void calculateVelocity();

	/**
	 * Abstract function to set the ParticleContainer
	 * @param pc_
	 */
	void setParticleContainer(ParticleContainer& pc_);

	ParticleContainer& getParticleContainer();

	/**
	 * Function to reset the force of all particles to zero
	 */
	void resetForce();

	/**
	 * Function to set the private parameter delta_t
	 * @param deltaT
	 */
	void setDeltaT(double deltaT);

	/**
	 * Function to get the private parameter delta_t
	 * @return delta_t
	 */
	double getDeltaT();

	void setLcDomain(LCDomain* lcDomain);

	LCDomain* getLcDomain();

	/**
	 * Function to calculate the force between the two specific particles p1 and p2
	 * @param p1
	 * @param p2
	 */
	static void calculateSingleForce(Particle* p1, Particle* p2);

	static void calculateLJInteraction(Particle* p, Particle* curP, double length, double cutOff);

	/**
	 * Function to calculate the force
	 */
	void calculateForce(double currentTime);


	/**
	 * Function to calculate velocity, position and force at once
	 */
	void calculateAll(double currentTime);

	static void calculateMembraneInteraction(Particle* p, Particle* curP, double length, double cutOff, int sidelength, double k, double r0, double r0sqrt, double mindist);


	int counterAll, counterMiss;
};






#endif /* CALCULATION_H_ */
