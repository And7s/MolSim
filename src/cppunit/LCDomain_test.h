/*
 * LCDomaintest.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paul
 */

#ifndef LCDOMAINTEST_H_
#define LCDOMAINTEST_H_

#include <cppunit/TestCase.h>
#include "LCDomain.h"

class LCDomain_test: public CppUnit::TestFixture {
protected:
	LCDomain* lcd;


public:
	LCDomain_test();
	virtual ~LCDomain_test();

	void setUp();
	void tearDown();

	/**
	 * test the general environment..
	 */
	void testEnvironment();

	void testBehaviour();

	void testCellResponds();
};

#endif /* LCDOMAINTEST_H_ */
