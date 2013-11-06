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

CppUnit::TestSuite *Tester::suite() {
	cout << "In Tester::suite()" << endl;
	CppUnit::TestSuite *suite_Tester = new CppUnit::TestSuite( "Tester_Suite" );
	suite_Tester->addTest(Calculation_suite::suite());
	suite_Tester->addTest(ParticleContainer_suite::suite());
	suite_Tester->addTest(Particle_suite::suite());
	return suite_Tester;
}
