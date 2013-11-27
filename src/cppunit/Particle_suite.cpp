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
	LOG4CXX_TRACE(loggerParticleTest, "In Particle_Suite: Particletests successful");

	return suite_Particle;
}

CppUnit::TestSuite* Particle_suite::singleSuite(std::string test) {
	std::string testArray[] = {"testAddOnF"};
	CppUnit::TestSuite *suite_Particle = new CppUnit::TestSuite( "Calculation_test" );
	int i=0;
	while(test.compare(testArray[i])!=0){
		i++;
	}
	LOG4CXX_TRACE(loggerParticleTest, "In Particle_SingleSuite: Starting Single Particletest " + test);
	switch(i){
	case 1:
		suite_Particle->addTest( new CppUnit::TestCaller<Particle_test>(
								   "testGetDeltaT",
								   &Particle_test::testAddOnF ) );
		break;
	default:
		LOG4CXX_WARN(loggerParticleTest, "Wrong input for singleTest: " << test);
		LOG4CXX_WARN(loggerParticleTest, "Use Input: " << testArray);
		LOG4CXX_WARN(loggerParticleTest, "In ParticleContainer_Suite: Single Test " + test + " unsuccessful");
		return suite_Particle;
	}
	LOG4CXX_TRACE(loggerParticleTest, "In Particle_SingleSuite: Single Particletest" + test + "successful");
	return suite_Particle;
}
