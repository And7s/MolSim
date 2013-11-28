/*
 * LCDomainsuite.h
 *
 *  Created on: Nov 28, 2013
 *      Author: friedrich
 */

#ifndef LCDOMAINSUITE_H_
#define LCDOMAINSUITE_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include "LCDomain_test.h"

/*
 *
 */
class LCDomain_suite {
public:
	LCDomain_suite();
	virtual ~LCDomain_suite();

	static CppUnit::TestSuite *suite();
	static CppUnit::TestSuite* singleSuite(std::string test);
};

#endif /* LCDOMAINSUITE_H_ */
