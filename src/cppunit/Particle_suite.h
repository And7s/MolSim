/*
 * Particle_suite.h
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */

#ifndef PARTICLE_SUITE_H_
#define PARTICLE_SUITE_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include "Particle_test.h"
/*
 *
 */
class Particle_suite{
public:
	Particle_suite();
	virtual ~Particle_suite();

	static CppUnit::TestSuite *suite();
};

#endif /* PARTICLE_SUITE_H_ */
