/*
 * Calculation_suite.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */

#include "Calculation_suite.h"

Calculation_suite::Calculation_suite() {
	// TODO Auto-generated constructor stub

}

Calculation_suite::~Calculation_suite() {
	// TODO Auto-generated destructor stub
}

CppUnit::TestSuite* Calculation_suite::suite() {
	cout << "In Calculation_suite::suite()" << endl;
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


	return suite_Calculation;
}
