/*
 * LCDomain.h
 *
 *  Created on: Nov 26, 2013
 *      Author: paul
 */

#ifndef LCDOMAIN_H_
#define LCDOMAIN_H_

#include <string.h>
#include "ParticleContainer.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include "help_macros.h"


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

	ParticleContainer** cells;

	/**
	 * this field stores direct references to the boundary zone, to access it faster.
	 */
	ParticleContainer** boundaryZone;


	/**
	 * stores the bounds of the domain
	 */
	std::vector<int> bounds;

	/**
	 * all particles, which are part of the actual simulation
	 */
	std::vector<Particle*> particles;

	/**
	 * stores particles, which are temporarily created in the halo-zone, to remove them later.
	 */
	std::vector<Particle*> haloParts;

	/**
	 * stores the number of cells
	 */
	int numberOfCells;

	/**
	 * number of cells, which are located in the boundary zone
	 */
	int numberOfBZCells;

	/**
	 * cutOffRadius, which is not always equal to the length of an edge of a cell
	 */
	double cutOffRadius;

	/**
	 * the length of an edge
	 */
	double cellDimension;

	/**
	 * stores the size of the halo-border (in #cells)
	 */
	int haloSize;

public:
	/**
	 *
	 * @param bounds  domain space (amount of cells) in each direction
	 * 		IMPORTANT: this is the actual computation space, without the border and halo-region.
	 * @param cutOffRad the specific cutoff radius.
	 * @param cellDimension the length of an edge of a cell
	 *  - vector size determines the dimension
	 */
	LCDomain(std::vector<int>* bounds, double cutOffRad, double cellDimension);

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
	void getNeighbourCells(ParticleContainer* cell, std::vector<ParticleContainer*>* neighbours);

	int getDimension();

	/**
	 *
	 * @param position size of the vector has to match the dimensions
	 * returns the requested cell
	 */
	ParticleContainer* getCellAt(std::vector<int>& position);


	/**
	 * assigns a particle to its corresponding cell
	 */
	void insertParticle(Particle* part);

	void insertParticles(std::vector<Particle*>& part);

	/**
	 * checks whether the input vector specifies a position, which is valid in this domain.
	 */
	bool checkBounds(std::vector<int>& position);

	/**
	 *
	 *
	 * since we have return value optimization, it is not to bad to return the value like this..
	 * furthermore the vector's size is most likely not higher than 3. copying this is not too bad.
	 *
	 * @return the x(y)(z) position of the cell
	 */
	std::vector<int> decodeDimensinalOrigin(int index);

	ParticleContainer**& getCells();

	ParticleContainer**& getHaloCells();

	void setCells(ParticleContainer**& cells);

	/**
	 * Reassigns the particles to their cells.
	 */
	void reset();

	void resetafter();

	void addHaloParticle(Particle* part);

	double getCutOffRadius();

	int getCellDimension();

	int getNumberOfCells();

	/**
	 * Number of cells in the boundary zone
	 */
	int getNumberOfBZCells();

	int getHaloSize();

	std::vector<Particle*>* getAllParticles();

	/**
	 *  @return true, in case that the Cell is located in the boundary region.
	 */
	bool isBoundaryCell(ParticleContainer& cell);

	/**
	 * delete a certain particle from the LCDomain, but not from RAM.
	 */
	void deleteParticle(Particle* particle);

	std::vector<int> getBounds();

	/**
	 * an array, storing the offset values. In an 3 dimensional domain, this array has a size of 2.
	 */
	int* getOffset();
};

#endif /* LCDOMAIN_H_ */
