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

}

void LCDomain_test::tearDown(){

}

void LCDomain_test::testEnvironment(){

	std::vector<int> vec1 (2,0);
	std::vector<int> vec2 (2,0);
	std::vector<LCell*> vec3;
	vec1[0] = 7;
	vec1[1] = 10;
	//vec1[2] = 19;

	vec2[0] = 2;
	vec2[1] = 2;
	//vec2[2] = 14;

	LCDomain* lcd = new LCDomain(&vec1);
	//LCell* lc = lcd->getCellAt(&vec2);
	//CPPUNIT_ASSERT_EQUAL(31,lc->getPosition());

	//lcd->getNeighbourCells(lc,&vec3);
	//int s = vec3.size();
	//CPPUNIT_ASSERT_EQUAL(3,s);
	//CPPUNIT_ASSERT_EQUAL(1, vec3[0]->getPosition());
	//CPPUNIT_ASSERT_EQUAL(6, vec3[1]->getPosition());
}

void LCDomain_test::testCellResponds(){

}

