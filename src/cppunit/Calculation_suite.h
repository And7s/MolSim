/*
 * Calculation_suite.h
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */

#ifndef CALCULATION_SUITE_H_
#define CALCULATION_SUITE_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include "Calculation_test.h"

/*
 *
 */
class Calculation_suite {
public:
	Calculation_suite();
	virtual ~Calculation_suite();

	static CppUnit::TestSuite *suite();
	static CppUnit::TestSuite* singleSuite(std::string test);
};

#endif /* CALCULATION_SUITE_H_ */
