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
 *CppUnit::TestSuite which contains the Tests for the class Particle
 */
class Particle_suite{
public:
	Particle_suite();
	virtual ~Particle_suite();

	static CppUnit::TestSuite *suite();
	static CppUnit::TestSuite *singleSuite(std::string test);
};

#endif /* PARTICLE_SUITE_H_ */
