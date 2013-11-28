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
	std::vector<int> vec (5,10);
	LCDomain lcd = new LCDomain(&vec);
	CPPUNIT_ASSERT_EQUAL(lcd.getDimension(),2);
}

