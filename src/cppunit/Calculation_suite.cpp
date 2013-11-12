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
