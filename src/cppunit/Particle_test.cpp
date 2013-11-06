/*
 * Particle_test.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: friedrich
 */

#include "Particle_test.h"

Particle_test::Particle_test() {
	// TODO Auto-generated constructor stub

}

Particle_test::~Particle_test() {
	// TODO Auto-generated destructor stub
}

void Particle_test::setUp() {
	double x1[] = {0,0,0};
	double x2[] = {1,1,1};
	double v1[] = {1,1,1};
	double v2[] = {2,2,2};
	double m1 = 1;
	double m2 = 2;
	particle1 = new Particle (x1, v1, m1);
	particle2 = new Particle (x2, v2, m2);
}

void Particle_test::tearDown() {
	delete particle1;
	delete particle2;
}

void Particle_test::testAddOnF() {
	utils::Vector<double,3> f;
	f[0]=1.0;
	f[1]=2.0;
	f[2]=3.0;
	utils::Vector<double,3> g;
	g[0]=3.0;
	g[1]=2.0;
	g[2]=1.0;
	particle1->setF(f);
	particle1->addOnF(g);
	utils::Vector<double,3> test;
	test[0]=4.0;
	test[1]=4.0;
	test[2]=4.0;

	CPPUNIT_ASSERT_EQUAL( test,particle1->getF());
}
