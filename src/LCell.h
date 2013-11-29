/*
 * Cell.h
 *
 *  Created on: Nov 26, 2013
 *      Author: paul
 */

#ifndef CELL_H_
#define CELL_H_

#include "Particle.h"

#include <list>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

class LCell {
	protected:
		/**
		 * contains all Paricles in this cell
		 */
		std::list<Particle*> items;

		std::list<Particle*>::iterator iter;

		/**
		 * the position of the cell in the domain
		 * this value is computed by the "DomainManager" and starts at 0
		 */
		int position;
	public:
		/**
		 * initialize new Cell with a unique id
		 */
		LCell(int p);

		/**
		 * destroy this cell
		 */
		~LCell();
		/**
		 * removes all items in this cell
		 * resets the counters
		 */
		void reset();

		/**
		 * adds a Particle at the end of the list
		 */
		void add(Particle * particle);

		/**
		 *
		 * @return the next Particle of the list. NULL, if end has been reached
		 */
		Particle* getNextItem();

		/**
		 *
		 */
		int getPosition();

};

#endif /* CELL_H_ */
