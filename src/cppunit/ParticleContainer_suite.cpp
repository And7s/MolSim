/*
 * ParticleContainer_suite.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */

#include "ParticleContainer_suite.h"

ParticleContainer_suite::ParticleContainer_suite() {
	// TODO Auto-generated constructor stub

}

ParticleContainer_suite::~ParticleContainer_suite() {
	// TODO Auto-generated destructor stub
}

CppUnit::TestSuite* ParticleContainer_suite::suite() {
	cout << "In ParticleContainer_suite::suite()" << endl;
	CppUnit::TestSuite *suite_ParticleContainer = new CppUnit::TestSuite( "ParticleContainer_test" );
	suite_ParticleContainer->addTest( new CppUnit::TestCaller<ParticleContainer_test>(
							   "testGetDeltaT",
							   &ParticleContainer_test::testGetLength ) );

	return suite_ParticleContainer;
}
