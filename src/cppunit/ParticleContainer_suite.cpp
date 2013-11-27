/*
 * ParticleContainer_suite.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */

#include "ParticleContainer_suite.h"

/**
 * Logger
 */
LoggerPtr loggerParticleContainerTest(Logger::getLogger( "main.particleContainerTest"));

ParticleContainer_suite::ParticleContainer_suite() {
	// TODO Auto-generated constructor stub

}

ParticleContainer_suite::~ParticleContainer_suite() {
	// TODO Auto-generated destructor stub
}

CppUnit::TestSuite* ParticleContainer_suite::suite() {
	LOG4CXX_TRACE(loggerParticleContainerTest, "In ParticleContainer_Suite: Starting ParticleContainertests");
	CppUnit::TestSuite *suite_ParticleContainer = new CppUnit::TestSuite( "ParticleContainer_test" );
	suite_ParticleContainer->addTest( new CppUnit::TestCaller<ParticleContainer_test>(
							   "testGetDeltaT",
							   &ParticleContainer_test::testGetLength ) );
	LOG4CXX_TRACE(loggerParticleContainerTest, "In ParticleContainer_Suite: ParticleContainertests succesful");

	return suite_ParticleContainer;
}

CppUnit::TestSuite* ParticleContainer_suite::singleSuite(std::string test) {
	string testArray[] = {"testGetLength"};
	CppUnit::TestSuite *suite_ParticleContainer = new CppUnit::TestSuite( "ParticleContainer_test" );
	int i = 0;
	while(test.compare(testArray[i])!=0){
		i++;
	}
	switch(i){
	case 0:
		LOG4CXX_TRACE(loggerParticleContainerTest, "In ParticleContainer_SingleSuite: Starting ParticleContainertest: " + test);
		suite_ParticleContainer->addTest( new CppUnit::TestCaller<ParticleContainer_test>(
									   "testGetDeltaT",
									   &ParticleContainer_test::testGetLength ) );
		break;
	default:
		LOG4CXX_WARN(loggerParticleContainerTest, "Wrong input for singleTest: " << test);
		LOG4CXX_WARN(loggerParticleContainerTest, "Use Input: " << testArray);
		LOG4CXX_WARN(loggerParticleContainerTest, "In ParticleContainer_Suite: Single Test " + test + " unsuccessful");
		return suite_ParticleContainer;
	}
	LOG4CXX_TRACE(loggerParticleContainerTest, "In ParticleContainer_SingleSuite: Single ParticleContainertest: " + test + "successful");
	return suite_ParticleContainer;
}
