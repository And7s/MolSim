/*
 * LCDomain.cpp
 *
 *  Created on: Nov 26, 2013
 *      Author: paul
 */

#include "LCDomain.h"

/**
 * Logger
 */
LoggerPtr loggerDomain(Logger::getLogger("main.domain"));

LCDomain::LCDomain(std::vector<int>* bounds) {
	dimension = bounds->size();
	this->bounds = bounds;
	switch (dimension) {
		case 1:
			//no need of an offset value
			break;
		case 2: case 3:
			offset = new int[dimension -1];
			int j;
			for(j = 0; j < dimension-1;j++){
				offset[j] = (*bounds)[j];
			}
			break;
		default:
			LOG4CXX_ERROR(loggerDomain, "unsupported dimension size! - unable to establish domain");
			return;
	}
	offset = new int[dimension - 1];
	int i;
	int linearspace = 1;
	for (i = 0; i < dimension - 1; i++) {
		offset[i] = (*bounds)[i];
	}
	for (i = 0; i < dimension; i++) {
		linearspace = linearspace * ((*bounds)[i]);
	}
	cells = new LCell*[linearspace];
	for (i = 0; i < linearspace; i++) {
		LCell* lc = new LCell(i);
		cells[i] = lc;
	}
	LOG4CXX_INFO(loggerDomain,
			"Domain generation finished --- dimensions: " << this->dimension << " Number of cells: " << linearspace);
}

LCell* LCDomain::getCellAt(std::vector<int> * pos) {
	if(!checkBounds(pos)){
		return NULL;
	}
	int index;
	switch (dimension) {
		case 1:
			return cells[(*pos)[0]];	//x
		case 2:
			return cells[(*pos)[1] * (offset[0]) + (*pos)[0]];	//y * offsetX + x
		case 3:
			return cells[(*pos)[2] * offset[0] * offset[1] + (*pos)[1] * offset[0] + (*pos)[0]]; //z * offsetX * offsetY + y * offsetX + x
		default:
			//can't happen
			return NULL;
	}
}

void LCDomain::getNeighbourCells(LCell * cell,std::vector<LCell*>* neighbours) {
	//decompose the 1D position into its higher dimensional origin.

	std::vector<int> axis (dimension,0);
	int pos = cell->getPosition();
	switch(dimension){
	case 3:
		axis[2] = pos / (offset[0] * offset[1]);
		pos = pos - (axis[2] * offset[1] * offset[0]);
	case 2:
		axis[1] = (pos / (offset[0]));
		pos = pos - (axis[1] * offset[0]);
	case 1:
		axis[0] = pos;
		break;
	default:
		LOG4CXX_ERROR(loggerDomain,"unsupported dimension size!");	//cant happen
		return;
	}

	//check, if the input cell's position is valid.

	if(!checkBounds(&axis)){
		LOG4CXX_ERROR(loggerDomain,"invalid input cell");
	}

	//gather actual neighbours
	std::vector<int> reference (axis);
	int x,y,z;
	switch(dimension){
	case 1:
		if(axis[0] > 0){
			reference[0] = axis[0] -1;
			neighbours->push_back(getCellAt(&reference));
			LOG4CXX_INFO(loggerDomain,"added: " << getCellAt(&reference)->getPosition());
		}
		LOG4CXX_INFO(loggerDomain,(axis)[0]);
		if(axis[0] < (*bounds)[0]-1){
			reference[0] = axis[0] +1;
			neighbours->push_back(getCellAt(&reference));
			LOG4CXX_INFO(loggerDomain,"added: " << getCellAt(&reference)->getPosition());
		}
		break;
	case 2:
		for(x=(axis[0]-1); x < (axis[0]+2);x++){
			for(y=(axis[1]-1); y < (axis[1]+2);y++){
				if((x >= 0) && (x < (*bounds)[0]) && (y >= 0) && (y < (*bounds)[1])){
					if(!(x == axis[0] && y == axis[1])){
						reference[0] = x;
						reference[1] = y;
						neighbours->push_back(getCellAt(&reference));
						LOG4CXX_INFO(loggerDomain,"added: " << getCellAt(&reference)->getPosition());
					}
				}
			}
		}
		break;
	case 3:
		for(x=(axis[0]-1); x < (axis[0]+2);x++){
			for(y=(axis[1]-1); y < (axis[1]+2);y++){
				for(z=(axis[2]-1); z < (axis[2]+2);z++){
					if((x >= 0) && (x < (*bounds)[0])
							&& (y >= 0) && (y < (*bounds)[1])
							&& (z >= 0) && (z < (*bounds)[2])){
						if(!(x == axis[0] && y == axis[1] && z == axis[2])){
							reference[0] = x;
							reference[1] = y;
							reference[2] = z;
							neighbours->push_back(getCellAt(&reference));
							LOG4CXX_INFO(loggerDomain,"added: " << getCellAt(&reference)->getPosition());
						}
					}
				}
			}
		}
		break;
	default:
		LOG4CXX_ERROR(loggerDomain,"unsupported dimension size!");	//cant happen
		return;
	}
}

bool LCDomain::checkBounds(std::vector<int>* pos) {
	if (pos->size() != dimension) {
		LOG4CXX_ERROR(loggerDomain,
				"Non-matching dimensions! Domain is currently set to " << this->dimension << " dimensions!");
		return false;
	}
	int i;
	for(i=0; i < dimension; i++){
		if(((*pos)[i] < 0) || ((*pos)[i] > (*bounds)[i])){
			LOG4CXX_ERROR(loggerDomain,"The requested position is not located in the domain space.");
			return false;
		}
	}
	return true;
}

int LCDomain::getDimension() {
	return dimension;
}

