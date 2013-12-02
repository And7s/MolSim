/*
 * ParticleContainer_test.cpp
 *
 *  Created on: Nov 5, 2013
 *      Author: friedrich
 */

#include "ParticleContainer_test.h"

ParticleContainer_test::ParticleContainer_test() {
	// TODO Auto-generated constructor stub

}

ParticleContainer_test::~ParticleContainer_test() {
	// TODO Auto-generated destructor stub
}

void ParticleContainer_test::setUp() {
	//Particle** pa = new Particle*[2];
	std::vector<Particle> pa;
	particleContainer = new ParticleContainer(2);
	Particle* p = new Particle();
	pa.push_back(*p);
	pa.push_back(*p);
	//pa[0] = new Particle();
	//pa[1] = new Particle();
	particleContainer->setParticles(pa);
}

void ParticleContainer_test::tearDown() {
	delete particleContainer;
}

void ParticleContainer_test::testGetLength() {
	CPPUNIT_ASSERT_EQUAL( 2, particleContainer->getLength() );
}
