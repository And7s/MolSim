#include "ParticleContainer.h"

/**
 * Interface for Calculation
 */
class Calculation{

private:
	ParticleContainer particleContainer;
	int delta_t;

public:

	virtual ~Calculation(){}
	/**
	 * Abstract function to calculate the force as described in Sheet1
	 */
	virtual void calculateForce()=0;
	/**
	 * Abstract function to calculate the position as described in Sheet1
	 */
	virtual void calculatePosition()=0;
	
	/**
	 * Abstract function to calculate the velocity as described in Sheet1
	 */
	virtual void calculateVelocity()=0;

	/**
	 * Function to reset the force of all particles to zero
	 */
	void resetForce();

	/**
	 * Function to set the private parameter delta_t
	 * @param deltaT
	 */
	void setDeltaT(int deltaT);

	/**
	 * Function to get the private parameter delta_t
	 * @return delta_t
	 */
	int getDeltaT();

	/**
	 * Function to get the reference to the private ParticleContainer
	 * @return particleContainer
	 */
	ParticleContainer& getParticleContainer();

	/**
	 * Function to set the reference of the private ParticleContainer
	 * @param particleContainer
	 */
	void setParticleContainer(ParticleContainer& particleContainer);
};

/**
 * Actual Implementation of the calculation of force, velocity and position, derived from Calculation
 */
class Sheet1Calc : public Calculation{

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
};

