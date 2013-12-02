/*
 * LCDomain.h
 *
 *  Created on: Nov 26, 2013
 *      Author: paul
 */

#ifndef LCDOMAIN_H_
#define LCDOMAIN_H_


#include "LCell.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;



/**
 * representing the Linked Cell Domain - a discrete environment
 *
 * IMPORTANT: Keep in mind, that the domain-bounds will behave equally to arrays.
 * If the domain has been set to 10 cells in x-direction,
 * the user is able to access cells from x equals 0 to 9.
 */
class LCDomain {
protected:
	int dimension;
	/**
	 * stores the offset. The array has one entry less than the dimension count.
	 * This ensures a proper handling with an one-dimensional array.
	 */
	int* offset;

	LCell** cells;

	/**
	 * stores the bounds of the domain
	 */
	std::vector<int> bounds;

	/**
	 * stores the number of cells
	 */
	int numberOfCells;

	/**
	 * cutOffRadius = length of an edge of a cell
	 */
	int cutOffRadius;

public:
	/**
	 *
	 * @param bounds  domain space (amount of cells) in each direction
	 *  - vector size determines the dimension
	 */
	LCDomain(std::vector<int>* bounds);

	/**
	 * The maximum size of the returned vector with respect to the dimension:
	 * 1D : 2
	 * 2D : 8
	 * 3D : 26
	 *
	 * @param cell the center
	 * @param neighbours the neighbour vector, which will be filled with values.
	 * @return this method will return all neighbour-cells of the input cell.
	 *  If the center-cell is part of the border,
	 *  the number of the returned cells in the vector will be reduced accordingly.
	 */
	void getNeighbourCells(LCell* cell, std::vector<LCell*>* neighbours);

	int getDimension();

	/**
	 *
	 * @param position size of the vector has to match the dimensions
	 * returns the requested cell
	 */
	LCell* getCellAt(std::vector<int>* position);


	/**
	 * assigns a particle to its corresponding cell
	 */
	void insertParticle(Particle* part);

	/**
	 * checks whether the input vector specifies a position, which is valid in this domain.
	 */
	bool checkBounds(std::vector<int>* position);

	/**
	 *
	 *
	 * since we have return value optimization, it is not to bad to return the value like this..
	 * furthermore the vector's size is most likely not higher than 3. copying this is not too bad.
	 *
	 * @return the x(y)(z) position of the cell
	 */
	std::vector<int> decodeDimensinalOrigin(int index);

	LCell**& getCells();

	void setCells(LCell**& cells);

	//TODO: implementation in header?
	int getNumberOfCells(){
		return numberOfCells;
	}

	//TODO: why this one? the number should computed correctly and stays constant over time
	void setNumberOfCells(int numberOfCells) {
		this->numberOfCells = numberOfCells;
	}

	void setCutOffRadius(int cutOffRad);

	int getCutOffRadius();
};

#endif /* LCDOMAIN_H_ */
