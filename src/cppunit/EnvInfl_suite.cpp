/*
 * EnvInflsuite.cpp
 *
 *  Created on: Jan 9, 2014
 *      Author: paul
 */

#include "EnvInfl_suite.h"

LoggerPtr loggerEnvInflTest(Logger::getLogger( "main.envInflTest"));

EnvInfl_suite::EnvInfl_suite() {
	// TODO Auto-generated constructor stub

}

EnvInfl_suite::~EnvInfl_suite() {
	// TODO Auto-generated destructor stub
}

CppUnit::TestSuite* EnvInfl_suite::suite() {
	LOG4CXX_WARN(loggerEnvInflTest, "In EnvInfl Test Suite: Starting LCDomaintests");
}

CppUnit::TestSuite* EnvInfl_suite::singleSuite(std::string test) {
	std::string testArray[] = {"testEnvInfl"};
	CppUnit::TestSuite *suite_EnvInfl = new CppUnit::TestSuite( "EnvInfl_test" );
	int i=0;
	while(i < 1 && test.compare(testArray[i])!=0){
		i++;
	}
	LOG4CXX_INFO(loggerEnvInflTest, "In EnvInfl_suite. Starting test: " << test << i);
	switch(i){
	case 0:
		std::cout << "starting test...." << std::endl << std::endl;
		suite_EnvInfl->addTest	( new CppUnit::TestCaller<EnvInfl_test>(
											   "testBasicBehaviour",
											   &EnvInfl_test::testBasicBehaviour ) );
		break;
	}
	return suite_EnvInfl;
}


