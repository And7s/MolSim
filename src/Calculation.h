#ifndef CALCULATION_H_
#define CALCULATION_H_

#include "ParticleContainer.h"
#include "LCDomain.h"

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>


using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/**
 * Interface for Calculation
 */
class Calculation {

protected:
	LCDomain lcDomain;
	ParticleContainer particleContainer;
	double delta_t;


public:
	virtual ~Calculation() {
	}
	/**
	 * Abstract function to calculate the force
	 */
	virtual void calculateForce()=0;
	/**
	 * Abstract function to calculate the position
	 */
	void calculatePosition();

	/**
	 * Abstract function to calculate the velocity
	 */
	void calculateVelocity();

	/**
	 * Abstract function to calculate velocity, position and force at once
	 */
	virtual void calculateAll()=0;

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

	void setLcDomain(LCDomain& lcDomain);

	LCDomain& getLcDomain();

	void calculateSingleForce(Particle* p1, Particle* p2);
};

/**
 * Actual Implementation of the calculation of force, velocity and position, derived from Calculation
 */
class Sheet1Calc: public Calculation {

public:
	/**
	 * Function to calculate the force as described in Sheet1
	 */
	void calculateForce();

	/**
	 * Function to calculate velocity, position and force at once as described in Shee1
	 */
	void calculateAll();
};

class Sheet2Calc: public Calculation {
public:
	/**
	 * Function to calculate the force as described in Sheet1
	 */
	void calculateForce();

	/**
	 * Function to calculate velocity, position and force at once as described in Shee1
	 */
	void calculateAll();
};

class Sheet3Calc: public Calculation {
public:
	/**
	 * Function to calculate the force as described in Sheet1
	 */
	void calculateForce();

	/**
	 * Function to calculate velocity, position and force at once as described in Shee1
	 */
	void calculateAll();

	static void calculateSingleForce(Particle* p1, Particle* p2);
};


#endif /* CALCULATION_H_ */
