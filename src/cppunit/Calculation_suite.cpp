/*
 * Calculation_suite.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */

#include "Calculation_suite.h"

/**
 * Logger
 */
LoggerPtr loggerCalcTest(Logger::getLogger( "main.calcTest"));

Calculation_suite::Calculation_suite() {
	// TODO Auto-generated constructor stub

}

Calculation_suite::~Calculation_suite() {
	// TODO Auto-generated destructor stub
}

CppUnit::TestSuite* Calculation_suite::suite() {
	LOG4CXX_TRACE(loggerCalcTest, "In Calculation_Suite: Starting Calculationtests");
	CppUnit::TestSuite *suite_Calculation = new CppUnit::TestSuite( "Calculation_test" );
	suite_Calculation->addTest( new CppUnit::TestCaller<Calculation_test>(
							   "testGetDeltaT",
							   &Calculation_test::testGetDeltaT ) );
	suite_Calculation->addTest( new CppUnit::TestCaller<Calculation_test>(
									"testCalculateForce",
									&Calculation_test::testCalculateForce ) );
	suite_Calculation->addTest( new CppUnit::TestCaller<Calculation_test>(
									"testCalculatePosition",
									&Calculation_test::testCalculatePosition ) );
	suite_Calculation->addTest( new CppUnit::TestCaller<Calculation_test>(
									"testCalculateVelocity",
									&Calculation_test::testCalculateVelocity ) );

	LOG4CXX_TRACE(loggerCalcTest, "In Calculation_Suite: Calculationtests succesful");
	return suite_Calculation;
}

CppUnit::TestSuite* Calculation_suite::singleSuite(std::string test) {
	std::string testArray[] = {"testGetDeltaT","testCalculateForce","testCalculatePosition", "testCalculateVelocity"};
	CppUnit::TestSuite *suite_Calculation = new CppUnit::TestSuite( "Calculation_test" );
	int i=0;
	while(test.compare(testArray[i])!=0){
		i++;
	}
	LOG4CXX_TRACE(loggerCalcTest, "In Calculation_SingleSuite: Starting Calculationtest: " + test);
	switch(i){
	case 0:
		suite_Calculation->addTest( new CppUnit::TestCaller<Calculation_test>(
									   "testGetDeltaT",
									   &Calculation_test::testGetDeltaT ) );
		break;
	case 1:
		suite_Calculation->addTest( new CppUnit::TestCaller<Calculation_test>(
										"testCalculateForce",
										&Calculation_test::testCalculateForce ) );
		break;
	case 2:
		suite_Calculation->addTest( new CppUnit::TestCaller<Calculation_test>(
										"testCalculatePosition",
										&Calculation_test::testCalculatePosition ) );
		break;
	case 3:
		suite_Calculation->addTest( new CppUnit::TestCaller<Calculation_test>(
										"testCalculateVelocity",
										&Calculation_test::testCalculateVelocity ) );
		break;
	default:
		LOG4CXX_WARN(loggerCalcTest, "Wrong input for singleTest: " << test);
		LOG4CXX_WARN(loggerCalcTest, "Use Input: " << testArray);
		LOG4CXX_WARN(loggerCalcTest, "In Calculation_Suite: Single Test " + test + " unsuccessful");
		return suite_Calculation;

	}
	LOG4CXX_TRACE(loggerCalcTest, "In Calculation_SingleSuite: Single Calculationtest: " + test + "successful");
	return suite_Calculation;
}
