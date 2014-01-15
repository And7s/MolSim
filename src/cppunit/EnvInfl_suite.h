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
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include "EnvInfl_test.h"

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

class EnvInfl_suite {
public:
	EnvInfl_suite();
	virtual ~EnvInfl_suite();


	static CppUnit::TestSuite* suite();
	static CppUnit::TestSuite* singleSuite(std::string test);
};

#endif /* ENVINFLSUITE_H_ */
