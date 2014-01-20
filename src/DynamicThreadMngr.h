/*
 * DynamicThreadMngr.h
 *
 *  Created on: Jan 15, 2014
 *      Author: paul
 */

#ifndef DYNAMICTHREADMNGR_H_
#define DYNAMICTHREADMNGR_H_

#include "LCDomain.h"
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

class DynamicThreadMngr {
public:
	DynamicThreadMngr();
	virtual ~DynamicThreadMngr();


	/**
	 * This method balances the particles, each thread has to handle.
	 * The thread-space-borders are adjusted along the x-axis (which is assumed to be the longest).
	 * In the end, the time all threads have to wait at their barriers should be reduced significantly,
	 * because all of them reach it in a smaller time interval.
	 *
	 * Call this method only once in a while (every 10000 calculation loops).
	 *
	 * @param a reference to the LCDomain
	 * @param the number of threads - which are active duringt the actual calulation
	 *
	 * @return an int Array - which is indicates the optimal border placements.
	 */
	static void optimizeThreadSpace(LCDomain& domain, int threads, int particleSize);

	static const int OPT_LOOPS = 10;

	static std::vector<ParticleContainer*>* getComputingSpace(int threadNum);


private:
	/**
	 * some helper function
	 * returns the border which has the largest gradient.
	 * The Maximum of second derive (in a discrete way)
	 */
	static int computeLargestGradient(int** input, int size);

	static std::vector<ParticleContainer*>* threadContainer;

};

#endif /* DYNAMICTHREADMNGR_H_ */
