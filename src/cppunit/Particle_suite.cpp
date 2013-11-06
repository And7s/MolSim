/*
 * Particle_suite.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */

#include "Particle_suite.h"

Particle_suite::Particle_suite() {
	// TODO Auto-generated constructor stub

}

Particle_suite::~Particle_suite() {
	// TODO Auto-generated destructor stub
}

CppUnit::TestSuite* Particle_suite::suite() {
	cout << "In Particle_suite::suite()" << endl;
	CppUnit::TestSuite *suite_Particle = new CppUnit::TestSuite( "Particle_test" );
	suite_Particle->addTest( new CppUnit::TestCaller<Particle_test>(
							   "testGetDeltaT",
							   &Particle_test::testAddOnF ) );

	return suite_Particle;
}
