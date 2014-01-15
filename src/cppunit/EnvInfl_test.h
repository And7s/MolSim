/*
 * EnvInfl_test.h
 *
 *  Created on: Jan 14, 2014
 *      Author: paul
 */

#ifndef ENVINFL_TEST_H_
#define ENVINFL_TEST_H_

#include <cppunit/TestCase.h>

class EnvInfl_test: public CppUnit::TestFixture {
public:
	EnvInfl_test();
	virtual ~EnvInfl_test();

	void setUp();
	void tearDown();

	/**
	 * test basic behaviour
	 */
	void testBasicBehaviour();
};

#endif /* ENVINFL_TEST_H_ */
