/*
 * Particle_test.h
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */

#ifndef PARTICLE_TEST_H_
#define PARTICLE_TEST_H_

#include <cppunit/TestCase.h>
#include <ParticleContainer.h>
#include <cppunit/extensions/HelperMacros.h>

/*
 *CppUnit::TestFixture defining the actual tests of the class Particle
 */
class Particle_test: public CppUnit::TestFixture {
private:
	Particle* particle1;
	Particle* particle2;

public:
	Particle_test();
	virtual ~Particle_test();

	void setUp();
	void tearDown();

	/**
	 * Function to test AddOnF()
	 */
	void testAddOnF();
};

#endif /* PARTICLE_TEST_H_ */
