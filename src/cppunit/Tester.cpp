/*
 * Tester.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */
#include "Tester.h"

Tester::Tester() {
	// TODO Auto-generated constructor stub

}

Tester::~Tester() {
	// TODO Auto-generated destructor stub
}

/**
 * Logger
 */
LoggerPtr loggerTester(Logger::getLogger( "main.Tester"));

CppUnit::TestSuite *Tester::suite() {
	LOG4CXX_TRACE(loggerTester, "In Tester_Suite: Starting Tests");
	CppUnit::TestSuite *suite_Tester = new CppUnit::TestSuite( "Tester_Suite" );
	suite_Tester->addTest(Calculation_suite::suite());
	suite_Tester->addTest(ParticleContainer_suite::suite());
	suite_Tester->addTest(Particle_suite::suite());
	LOG4CXX_TRACE(loggerTester, "In Tester_Suite: All Tests successful");
	return suite_Tester;
}
