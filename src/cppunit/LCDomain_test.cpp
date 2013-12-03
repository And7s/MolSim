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
	this->lcd = new LCDomain(&dim);
	this->lcd->setCutOffRadius(3);
}

void LCDomain_test::tearDown(){
	//delete lcd;
}

/**
 * CAUTION!! currently it is not possible to execute both tests with a single program call..
 * There is now proper cleanup and therefore the second test will most likly fail.
 */

void LCDomain_test::testEnvironment(){
	CPPUNIT_ASSERT_EQUAL(2,lcd->getDimension());
	CPPUNIT_ASSERT_EQUAL(50,lcd->getNumberOfCells());

}

void LCDomain_test::testBehaviour(){
	/*std::vector<int> pos (3,0);
	std::vector<LCell*> cells;
	pos[0] = 2;
	pos[1] = 3;
	pos[2] = 4;
	LCell* cell = lcd->getCellAt(pos);
	//CPPUNIT_ASSERT_EQUAL(17, cell->getPosition());
	lcd->getNeighbourCells(cell,&cells);
	int i = cells.size();
	CPPUNIT_ASSERT_EQUAL(26, i);

	//add some particles
	double x[] = {10,1,1};
	double v[] = {1,1,1};
	Particle* p1 = new Particle(x, v , 1.0, 1);
	Particle* p2 = new Particle(x, v, 1.0 ,1);
	Particle* p3 = new Particle(x, v, 1.0 ,1);

	this->lcd->insertParticle(p1);
	this->lcd->insertParticle(p2);
	this->lcd->insertParticle(p3);

	pos[0] = 3;
	pos[1] = 0;
	pos[2] = 0;
	cell = this->lcd->getCellAt(pos);
	Particle* pp;
	while((pp = cell->getNextItem()) != NULL){
		std::cout << pp->getType() << std::endl;
	}

*/
}

void LCDomain_test::testCellResponds(){

}

