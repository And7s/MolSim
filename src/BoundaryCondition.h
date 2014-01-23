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

	void apply();
	
	void applySwitch(int type,std::vector<int>& pos, int axis, bool zero);
	void applyOutflow(ParticleContainer* pc);
	void applyReflecting(ParticleContainer* pc, int axis, bool zero);
	void applyPeriodic(ParticleContainer* pc, ParticleContainer* pc2, int axis, bool zero, std::vector<int>& posCell);
};

#endif /* BOUNDARYCONDITION_H_ */
