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
 *CppUnit::TestFixture defining the actual tests of the class Calculation
 */
class Calculation_test: public CppUnit::TestFixture {
private:
	Calculation* test_calculator;

public:
	Calculation_test();
	virtual ~Calculation_test();

	void setUp();
	void tearDown();

	/**
	 * Function for to test GetDeltaT()
	 */
	void testGetDeltaT();
	/**
	 * Function to test CalculateForce()
	 */
	void testCalculateForce();
	/**
	 * Function to test CalculatePosition()
	 */
	void testCalculatePosition();
	/**
	 * Function to test CalculateVelocity
	 */
	void testCalculateVelocity();
};

#endif /* CALCULATION_TEST_H_ */
