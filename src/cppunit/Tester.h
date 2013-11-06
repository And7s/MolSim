/*
 * Tester.h
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */

#ifndef TESTER_H_
#define TESTER_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include "Calculation_suite.h"
#include "ParticleContainer_suite.h"
#include "Particle_suite.h"

/*
 *
 */
class Tester: public CppUnit::TestFixture {
public:
	Tester();
	virtual ~Tester();

	static CppUnit::TestSuite *suite();
};

#endif /* TESTER_H_ */
