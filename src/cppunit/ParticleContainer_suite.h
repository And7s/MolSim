/*
 * ParticleContainer_suite.h
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */

#ifndef PARTICLECONTAINER_SUITE_H_
#define PARTICLECONTAINER_SUITE_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include "ParticleContainer_test.h"

/*
 *CppUnit::TestSuite which contains the Tests for the class ParticleContainer
 */
class ParticleContainer_suite {
public:
	ParticleContainer_suite();
	virtual ~ParticleContainer_suite();

	static CppUnit::TestSuite *suite();
	static CppUnit::TestSuite *singleSuite(std::string test);
};

#endif /* PARTICLECONTAINER_SUITE_H_ */
