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

CppUnit::TestSuite *Tester::singleSuite(std::string test) {
	int numberOfTests = 9;
	string testArray[] = {"testGetDeltaT","testCalculateForce","testCalculatePosition", "testCalculateVelocity", "testGetLength",
			"testAddOnF", "testDomainEnv", "testDomainBehaviour", "testEnvInfl"};
	int i=0;
	while(test.compare(testArray[i])!=0 && i<=numberOfTests){
		i++;
	}
	LOG4CXX_TRACE(loggerTester, "In Tester_SingleSuite: Starting SingleTests: " + test);
	CppUnit::TestSuite *suite_Tester = new CppUnit::TestSuite( "Tester_Suite" );
	if(i<4){
		LOG4CXX_TRACE(loggerTester, "In Tester_SingleSuite: Test: " + test);
		LOG4CXX_TRACE(loggerTester, "Starting Calculation_suite");
		suite_Tester->addTest(Calculation_suite::singleSuite(test));
	}else if(i==4){
		LOG4CXX_TRACE(loggerTester, "In Tester_SingleSuite: Test " + test + " successful");
		LOG4CXX_TRACE(loggerTester, "Starting ParticleContainer_suite");
		suite_Tester->addTest(ParticleContainer_suite::singleSuite(test));
	}else if(i==5){
		LOG4CXX_TRACE(loggerTester, "In Tester_SingleSuite: Test " + test + " successful");
		LOG4CXX_TRACE(loggerTester, "Starting Particle_suite");
		suite_Tester->addTest(Particle_suite::singleSuite(test));
	}else if(i==6 || i==7){
		LOG4CXX_TRACE(loggerTester, "In Tester_SingleSuite: Test " + test + " successful");
		LOG4CXX_TRACE(loggerTester, "Starting LCDomain_suite");
		suite_Tester->addTest(LCDomain_suite::singleSuite(test));
	}else if(i==8){
		LOG4CXX_TRACE(loggerTester, "In Tester_SingleSuite: Test " + test + " successful");
		LOG4CXX_TRACE(loggerTester, "Starting EnvInfl_suite");
		suite_Tester->addTest(EnvInfl_suite::singleSuite(test));
	}else{
		LOG4CXX_WARN(loggerTester, "Wrong input for singleTest: " << test);
		LOG4CXX_WARN(loggerTester, "Use Input: ");
		for(int j = 0; j < numberOfTests; j++){
			LOG4CXX_WARN(loggerTester, testArray[j]);
		}
		LOG4CXX_WARN(loggerTester, "In Tester_SingleSuite: Test " + test + " unsuccessful");
		return suite_Tester;
	}
	LOG4CXX_TRACE(loggerTester, "In Tester_SingleSuite: Test " + test + " successful");
	return suite_Tester;
}
