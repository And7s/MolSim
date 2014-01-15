/*
 * DynamicThreadMngr.h
 *
 *  Created on: Jan 15, 2014
 *      Author: paul
 */

#ifndef DYNAMICTHREADMNGR_H_
#define DYNAMICTHREADMNGR_H_

#include "LCDomain.h"
#include <omp.h>

class DynamicThreadMngr {
public:
	DynamicThreadMngr();
	virtual ~DynamicThreadMngr();


	/**
	 *
	 */
	static int* optimizeThreadSpace(LCDomain& domain, int threads);

	static const int OPT_LOOPS = 10;

private:
	static int computeLargestGradient(int** input, int size);

};

#endif /* DYNAMICTHREADMNGR_H_ */
