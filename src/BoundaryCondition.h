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

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/**
 * Interface for BoundaryCondition
 */
class BoundaryCondition {

protected:
	LCDomain linkedCell;
	std::vector<int> domainSize;
	double sigma;
	double epsilon;
	std::string position;
	std::string boundaryType;

public:
	BoundaryCondition();

	BoundaryCondition(LCDomain& linkedCell, std::vector<int> domainSize);

	virtual ~BoundaryCondition();

	LCDomain& getLCDomain();

	void setLCDomain(LCDomain& linkedCell);

	/**
	 * Abstract function to check the Boundary Conditions
	 */
	virtual void applyBoundaryCondition(int* noOfParticles)=0;

	void setDomainSize(std::vector<int>& domainSize);

	void setSigma(double sigma);

	void setEpsilon(double epsilon);
	void setBoundaryType(std::string boundaryType);
	void setPosition(std::string position);
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
	void applyBoundaryCondition(int* noOfParticles);
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
	void applyBoundaryCondition(int* noOfParticles);

	/**
	 * Apply the counterreactive Forces of the "counter"-particle
	 * @param p
	 * @param axis
	 * @param orientation
	 */
	void applyForce(Particle* p, int axis, bool orientation);
};

#endif /* BOUNDARYCONDITION_H_ */
