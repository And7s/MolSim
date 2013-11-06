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
	std::list<Particle> particles;
	ParticleContainer pc(2);
	test_calculator = new Sheet1Calc();
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
	Particle p1(x1, v1, m1);
	Particle p2(x2, v2, m2);
	p1.setF(f1);
	p2.setF(f2);
	particles.push_back(p1);
	particles.push_back(p2);
	pc.setParticles(particles);
	test_calculator->setParticleContainer(pc);
	test_calculator->setDeltaT(5);
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
	result1[0]=-8.0;
	result1[1]=6.0;
	result1[2]=0.0;
	result2 = result1 *(-1);
	ParticleContainer pc = test_calculator->getParticleContainer();
	CPPUNIT_ASSERT_EQUAL( result1,  pc.getParticles()[0]->getF());
	CPPUNIT_ASSERT_EQUAL( result2,  pc.getParticles()[1]->getF());
}

void Calculation_test::testCalculatePosition() {
	test_calculator->calculatePosition();
	utils::Vector<double,3> result1;
	utils::Vector<double,3> result2;
	result1[0]=9.5;
	result1[1]=5.5;
	result1[2]=5.5;
	result2[0]=12.5;
	result2[1]=15.5;
	result2[2]=12.5;
	ParticleContainer pc = test_calculator->getParticleContainer();
	CPPUNIT_ASSERT_EQUAL( result1, pc.getParticles()[0]->getX() );
	CPPUNIT_ASSERT_EQUAL( result2, pc.getParticles()[1]->getX() );
}

void Calculation_test::testCalculateVelocity() {
	test_calculator->calculateVelocity();
	utils::Vector<double,3> result1;
	utils::Vector<double,3> result2;
	result1[0]=1.1;
	result1[1]=1.1;
	result1[2]=1.1;
	result2[0]=2.5;
	result2[1]=2.5;
	result2[2]=2.5;
	ParticleContainer pc = test_calculator->getParticleContainer();
	CPPUNIT_ASSERT_EQUAL( result1, pc.getParticles()[0]->getV() );
	CPPUNIT_ASSERT_EQUAL( result2, pc.getParticles()[1]->getV() );
}
