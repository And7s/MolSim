/*
 * Calculation_test.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */

#include "Calculation_test.h"

Calculation_test::Calculation_test() {
	// TODO Auto-generated constructor stub

}

Calculation_test::~Calculation_test() {
	// TODO Auto-generated destructor stub
}

void Calculation_test::setUp() {
	Particle** pa = new Particle*[2];
	ParticleContainer pc(2);

	test_calculator = new Sheet2Calc();

	double x1[] = {4,0,0};
	double x2[] = {0,3,0};
	double v1[] = {1,1,1};
	double v2[] = {2,2,2};

	utils::Vector<double,3> f1;
	f1[0]=1.0;
	f1[1]=1.0;
	f1[2]=1.0;
	utils::Vector<double,3> f2;
	f2[0]=2.0;
	f2[1]=2.0;
	f2[2]=2.0;

	double m1 = 25;
	double m2 = 10;
	pa[0] = new Particle(x1, v1, m1);
	pa[1] = new Particle(x2, v2, m2);
	pa[0]->setF(f1);
	pa[1]->setF(f2);
	
	pc.setParticles(pa);
	test_calculator->setParticleContainer(pc);
	test_calculator->setDeltaT(1);
}

void Calculation_test::tearDown() {
	delete test_calculator;
}

void Calculation_test::testGetDeltaT() {
	test_calculator->setDeltaT(2.);
	CPPUNIT_ASSERT_EQUAL( 2., test_calculator->getDeltaT() );
}

void Calculation_test::testCalculateForce() {
	test_calculator->calculateForce();
	utils::Vector<double,3> result1;
	utils::Vector<double,3> result2;
	result1[0]=-0.00122864;
	result1[1]=0.000921482;
	result1[2]=0.0;

	result2 = result1 *(-1);
	ParticleContainer pc = test_calculator->getParticleContainer();

	for(int i = 0;i < 3; i++) {
		CPPUNIT_ASSERT_DOUBLES_EQUAL(result1[i], pc.getParticles()[0]->getF()[i], 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(result2[i], pc.getParticles()[1]->getF()[i], 0.001);
	}
}

void Calculation_test::testCalculatePosition() {
	test_calculator->calculatePosition();
	utils::Vector<double,3> result1;
	utils::Vector<double,3> result2;
	result1[0]=5.02;
	result1[1]=1.02;
	result1[2]=1.02;

	result2[0]=2.1;
	result2[1]=5.1;
	result2[2]=2.1;
	
	ParticleContainer pc = test_calculator->getParticleContainer();

	for(int i = 0;i < 3; i++) {
		CPPUNIT_ASSERT_DOUBLES_EQUAL(result1[i], pc.getParticles()[0]->getX()[i], 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(result2[i], pc.getParticles()[1]->getX()[i], 0.001);
	}
}

void Calculation_test::testCalculateVelocity() {
	test_calculator->calculateVelocity();
	utils::Vector<double,3> result1;
	utils::Vector<double,3> result2;
	result1[0]=1.02;
	result1[1]=1.02;
	result1[2]=1.02;
	result2[0]=2.1;
	result2[1]=2.1;
	result2[2]=2.1;
	ParticleContainer pc = test_calculator->getParticleContainer();
	for(int i = 0;i < 3; i++) {
		CPPUNIT_ASSERT_DOUBLES_EQUAL(result1[i], pc.getParticles()[0]->getV()[i], 0.001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(result2[i], pc.getParticles()[1]->getV()[i], 0.001);
	}
}
