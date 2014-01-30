/*
 * LCDomainsuite.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: friedrich
 */

#include "LCDomain_suite.h"

/**
 * Logger
 */
LoggerPtr loggerLCDomainTest(Logger::getLogger( "main.lcDomainTest"));

LCDomain_suite::LCDomain_suite() {
	// TODO Auto-generated constructor stub
}

LCDomain_suite::~LCDomain_suite() {
	// TODO Auto-generated destructor stub
}

CppUnit::TestSuite* LCDomain_suite::suite() {
	LOG4CXX_TRACE(loggerLCDomainTest, "In LCDomain_Suite: Starting LCDomaintests");
	CppUnit::TestSuite *suite_LCDomain = new CppUnit::TestSuite( "LCDomain_test" );
	suite_LCDomain->addTest( new CppUnit::TestCaller<LCDomain_test>(
							   "testDomain",
							   &LCDomain_test::testEnvironment ) );
	//suite_LCDomain->addTest( new CppUnit::TestCaller<LCDomain_test>(
	//							   "testDomainBehaviour",
	//							   &LCDomain_test::testBehaviour ) );

	LOG4CXX_TRACE(loggerLCDomainTest, "In LCDomain_Suite: LCDomaintests succesful");
	return suite_LCDomain;
}

CppUnit::TestSuite* LCDomain_suite::singleSuite(std::string test) {
	std::string testArray[] = {"testDomainEnv","testDomainBehaviour"};
	CppUnit::TestSuite *suite_LCDomain = new CppUnit::TestSuite( "LCDomain_test" );
	int i=0;
	while(test.compare(testArray[i])!=0){
		i++;
	}
	LOG4CXX_TRACE(loggerLCDomainTest, "In LCDomain_SingleSuite: Starting LCDomaintest: " + test);
	switch(i){
	case 0:
		suite_LCDomain->addTest( new CppUnit::TestCaller<LCDomain_test>(
									   "testDomainEnv",
									   &LCDomain_test::testEnvironment ) );
		break;
	case 1:
		suite_LCDomain->addTest( new CppUnit::TestCaller<LCDomain_test>(
											   "testDomainBehaviour",
											   &LCDomain_test::testBehaviour ) );
		break;
	default:
		LOG4CXX_WARN(loggerLCDomainTest, "Wrong input for singleTest: " << test);
		LOG4CXX_WARN(loggerLCDomainTest, "Use Input: " << testArray);
		LOG4CXX_WARN(loggerLCDomainTest, "In LCDomain_Suite: Single Test " + test + " unsuccessful");
		return suite_LCDomain;

	}
	LOG4CXX_TRACE(loggerLCDomainTest, "In LCDomain_SingleSuite: Single LCDomaintest: " + test + "successful");
	return suite_LCDomain;
}
