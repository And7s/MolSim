/*
 * LCell.cpp
 *
 *  Created on: Nov 26, 2013
 *      Author: paul
 */

#include "LCell.h"

/**
 * Logger
 */
LoggerPtr loggerLCell(Logger::getLogger( "main.cell"));
/*
LCell::LCell(){
	this->position = -1; //indicates an error
}*/

LCell::LCell(int p){
	this->position = p;
	LOG4CXX_TRACE(loggerLCell,"created new cell at position: " << p);
}

LCell::~LCell(){
	//nothing to be done
}

void LCell::reset(){
	LOG4CXX_TRACE(loggerLCell, "removing particles from cell");
	//lösche
}

void LCell::add(Particle * particle){
	items.push_back(particle);
}



Particle* LCell::getNextItem(){
	iter = this->items.begin();
	if(iter != this->items.end()){
		return NULL;
	}
	Particle* temp = (*iter);
	iter++;
	return temp;
}

int LCell::getPosition(){
	return this->position;
}
