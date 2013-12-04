/*
 * LCDomaintest.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: paul
 */

#include "LCDomain_test.h"

LCDomain_test::LCDomain_test() {
	// TODO Auto-generated constructor stub

}

LCDomain_test::~LCDomain_test() {
	// TODO Auto-generated destructor stub
}

void LCDomain_test::setUp(){
	std::vector<int> dim;
	dim.push_back(5);
	dim.push_back(10);
	dim.push_back(7);
	this->lcd = new LCDomain(&dim,3,3);
}

void LCDomain_test::tearDown(){
	//delete lcd;
}

/**
 * CAUTION!! currently it is not possible to execute both tests with a single program call..
 * There is now proper cleanup and therefore the second test will most likly fail.
 */

void LCDomain_test::testEnvironment(){

	CPPUNIT_ASSERT_EQUAL(3,lcd->getDimension());
	CPPUNIT_ASSERT_EQUAL(350,lcd->getNumberOfCells());

}

void LCDomain_test::testBehaviour(){
	std::vector<int> pos (3,0);
	std::vector<ParticleContainer*> cells;
	pos[0] = 2;
	pos[1] = 3;
	pos[2] = 4;
	ParticleContainer* cell = lcd->getCellAt(pos);
	//CPPUNIT_ASSERT_EQUAL(17, cell->getPosition());
	lcd->getNeighbourCells(cell,&cells);
	int i = cells.size();
	CPPUNIT_ASSERT_EQUAL(26, i);

	//add some particles
	double x1[] = {9,1,1};
	double x2[] = {10,1,1};
	double x3[] = {11,1,1};
	double v[] = {1,1,1};
	Particle* p1 = new Particle(x1, v , 1.0, 1);
	Particle* p2 = new Particle(x2, v, 1.0 ,1);
	Particle* p3 = new Particle(x3, v, 1.0 ,1);

	this->lcd->insertParticle(p1);
	this->lcd->insertParticle(p2);
	this->lcd->insertParticle(p3);

	pos[0] = 3;
	pos[1] = 0;
	pos[2] = 0;
	cell = this->lcd->getCellAt(pos);
	cell->show();

	utils::Vector<double,3> p4;
	p4[0] = 11;
	p4[1] = 1;
	p4[2] = 1;

	utils::Vector<double,3> p5;
	p5[0] = 12;
	p5[1] = 1;
	p5[2] = 1;

	utils::Vector<double,3> p6;
	p6[0] = 13;
	p6[1] = 1;
	p6[2] = 1;

	p1->setX(p4);
	p2->setX(p5);
	p3->setX(p6);

	lcd->reset();
	std::cout << "showing cell 3:" <<std::endl;
	cell->show();
	pos[0] = 4;
	pos[1] = 0;
	pos[2] = 0;
	cell = this->lcd->getCellAt(pos);
	std::cout << "showing cell 4:" <<std::endl;
	cell->show();
}

void LCDomain_test::testCellResponds(){

}

