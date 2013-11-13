/*
 * ParticleContainer_test.h
 *
 *  Created on: Nov 5, 2013
 *      Author: friedrich
 */

#ifndef PARTICLECONTAINER_TEST_H_
#define PARTICLECONTAINER_TEST_H_

#include <cppunit/TestCase.h>
#include <ParticleContainer.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;

/*
 *CppUnit::TestFixture defining the actual tests of the class ParticleContainer
 */
class ParticleContainer_test: public CppUnit::TestFixture {
private:
	ParticleContainer* particleContainer;

public:
	ParticleContainer_test();
	virtual ~ParticleContainer_test();

	void setUp();
	void tearDown();

	/**
	 * Function to test GetLength()
	 */
	void testGetLength();
};

#endif /* PARTICLECONTAINER_TEST_H_ */
