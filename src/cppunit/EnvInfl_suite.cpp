/*
 * EnvInflsuite.cpp
 *
 *  Created on: Jan 9, 2014
 *      Author: paul
 */

#include "EnvInfl_suite.h"

LoggerPtr loggerEnvInflTest(Logger::getLogger( "main.lcDomainTest"));

EnvInfl_suite::EnvInfl_suite() {
	// TODO Auto-generated constructor stub

}

EnvInfl_suite::~EnvInfl_suite() {
	// TODO Auto-generated destructor stub
}

CppUnit::TestSuite* EnvInfl_suite::suite() {
	LOG4CXX_WARN(loggerEnvInflTest, "In LCDomain_Suite: Starting LCDomaintests");
}

CppUnit::TestSuite* EnvInfl_suite::singleSuite(std::string test) {

}


