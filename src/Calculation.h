#ifndef CALCULATION_H_
#define CALCULATION_H_

#include "ParticleContainer.h"

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
	virtual void calculatePosition()=0;

	/**
	 * Abstract function to calculate the velocity
	 */
	virtual void calculateVelocity()=0;

	/**
	 * Abstract function to calculate velocity, position and force at once
	 */
	virtual void calculateAll()=0;

	/**
	 * Abstract function to set the ParticleContainer
	 * @param pc_
	 */
	virtual void setParticleContainer(ParticleContainer& pc_)=0;

	virtual ParticleContainer& getParticleContainer()=0;

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
	 * Function to calculate the position as described in Sheet1
	 */
	void calculatePosition();
	/**
	 * Function to calculate the velocity as described in Sheet1
	 */
	void calculateVelocity();

	/**
	 * Function to calculate velocity, position and force at once as described in Shee1
	 */
	void calculateAll();

	/**
	 * Function to set the ParticleContainer
	 * @param pc_
	 */
	void setParticleContainer(ParticleContainer& pc_);

	ParticleContainer& getParticleContainer();
};

class Sheet2Calc: public Calculation {
public:
	/**
	 * Function to calculate the force as described in Sheet1
	 */
	void calculateForce();
	/**
	 * Function to calculate the position as described in Sheet1
	 */
	void calculatePosition();
	/**
	 * Function to calculate the velocity as described in Sheet1
	 */
	void calculateVelocity();

	/**
	 * Function to calculate velocity, position and force at once as described in Shee1
	 */
	void calculateAll();

	/**
	 * Function to set the ParticleContainer
	 * @param pc_
	 */
	void setParticleContainer(ParticleContainer& pc_);

	ParticleContainer& getParticleContainer();
};

#endif /* CALCULATION_H_ */
