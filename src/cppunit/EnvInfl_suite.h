/*
 * EnvInflsuite.h
 *
 *  Created on: Jan 9, 2014
 *      Author: paul
 */

#ifndef ENVINFLSUITE_H_
#define ENVINFLSUITE_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include "LCDomain_test.h"

class EnvInfl_suite {
public:
	EnvInfl_suite();
	virtual ~EnvInfl_suite();


	static CppUnit::TestSuite* suite();
	static CppUnit::TestSuite* singleSuite(std::string test);
};

#endif /* ENVINFLSUITE_H_ */
