/*
 * BoundaryCondition.h
 *
 *  Created on: Nov 27, 2013
 *      Author: friedrich
 */

#ifndef BOUNDARYCONDITION_H_
#define BOUNDARYCONDITION_H_

#include "LCDomain.h"
#include "Calculation.h"

/*
 *
 */
class BoundaryCondition {

protected:
	Calculation *calculation;
	LCDomain *linkedCell;
	utils::Vector<double, 3> domainSize;
	double sigma;

public:
	BoundaryCondition();

	BoundaryCondition(LCDomain* linkedCell, utils::Vector<double, 3> domainSize);

	virtual ~BoundaryCondition();

	LCDomain* getLCDomain();

	void setLCDomain(LCDomain* linkedCell);

	/**
	 * Abstract function to check the Boundary Conditions
	 */
	virtual void applyBoundaryCondition()=0;

	utils::Vector<double, 3> getDomainSize();

	Calculation*& getCalculation();

	void setCalculation(Calculation*& calculation);
};

/**
 * Actual Implementation of the Boundary Condition: Outflow Boundary, i.e.
 * particles are being removed when they cross the boundary of the domain
 */
class OutflowBoundary: public BoundaryCondition {

public:
	/**
	 * Function to apply the Boundary Conditions for OutflowBoundary
	 */
	void applyBoundaryCondition();
};

/**
 * Actual Implementation of the Boundary Condition: Reflecting Boundary, i.e.
 * particles are being reflected when being near the border by placing a "counter"-particle at the boundary
 */
class ReflectingBoundary: public BoundaryCondition {

public:
	/**
	 * Function to apply the Boundary Conditions for OutflowBoundary
	 */
	void applyBoundaryCondition();

	void applyForce(Particle* p, int axis, bool orientation);
};

#endif /* BOUNDARYCONDITION_H_ */
