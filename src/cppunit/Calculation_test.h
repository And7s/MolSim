/*
 * Calculation_test.h
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */

#ifndef CALCULATION_TEST_H_
#define CALCULATION_TEST_H_

#include <cppunit/TestCase.h>

#include "Calculation.h"
#include "Particle.h"

/*
 *
 */
class Calculation_test: public CppUnit::TestFixture {
private:
	Calculation* test_calculator;
	//ParticleContainer* test_pc;
	//std::list<Particle>* particles;

public:
	Calculation_test();
	virtual ~Calculation_test();

	void setUp();
	void tearDown();

	void testGetDeltaT();
	void testCalculateForce();
	void testCalculatePosition();
	void testCalculateVelocity();
};

#endif /* CALCULATION_TEST_H_ */
