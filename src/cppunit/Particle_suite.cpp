/*
 * Particle_suite.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */

#include "Particle_suite.h"

/**
 * Logger
 */
LoggerPtr loggerParticleTest(Logger::getLogger( "main.particleTest"));

Particle_suite::Particle_suite() {
	// TODO Auto-generated constructor stub

}

Particle_suite::~Particle_suite() {
	// TODO Auto-generated destructor stub
}

CppUnit::TestSuite* Particle_suite::suite() {
	LOG4CXX_TRACE(loggerParticleTest, "In Particle_Suite: Starting Particletests");
	CppUnit::TestSuite *suite_Particle = new CppUnit::TestSuite( "Particle_test" );
	suite_Particle->addTest( new CppUnit::TestCaller<Particle_test>(
							   "testGetDeltaT",
							   &Particle_test::testAddOnF ) );
	LOG4CXX_TRACE(loggerParticleTest, "In Particle_Suite: Particletests succesful");

	return suite_Particle;
}
