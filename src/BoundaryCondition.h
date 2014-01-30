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
#include "help_macros.h"

#include "input.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

#include <memory>   // std::auto_ptr
#include <iostream>

using namespace std;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/**
 * Interface for BoundaryCondition
 */
class BoundaryCondition {

protected:
	LCDomain* linkedCell;
	std::vector<int> domainSize;
	
	int dimension;
	int boundarytype[6];
	int* length;

public:
	
	BoundaryCondition(LCDomain* linkedCell_, std::vector<int> domainSize, int dimension_, auto_ptr<input_t>& inp, int* length_);

	~BoundaryCondition();

	/**
	 * Iterates through the Domain for each specific position pos = (x,y,z) and gives this pos, if it is outOfBounds with x and/or y and/or z,
	 * to applySwitch with the corresponding boundary on that side
	 */
	void apply();
	
	/**
	 * gets the position pos from apply and receives the corresponding cell from LCDomain. Afterwards gives this cell to the corresponding
	 * BoundaryCondition
	 * @param type
	 * @param pos
	 * @param axis
	 * @param zero
	 */
	void applySwitch(int type,std::vector<int>& pos, int axis, bool zero);

	/**
	 * Gets the particleContainer cell and applies the outflow condition on all particles in this cell
	 * @param pc
	 */
	void applyOutflow(ParticleContainer* pc);

	/**
	 * Gets the particleContainer cell and applies the reflecting condition on all particles in this cell
	 * @param pc
	 */
	void applyReflecting(ParticleContainer* pc, int axis, bool zero);

	/**
	 * Gets the particleContainer cell and applies the periodic condition on all particles in this cell
	 * @param pc
	 */
	void applyPeriodic(ParticleContainer* pc, ParticleContainer* pc2, int axis, bool zero, std::vector<int>& posCell);
};

#endif /* BOUNDARYCONDITION_H_ */
