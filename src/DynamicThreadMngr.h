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

	/**
	 * This method balances the particles, each thread has to handle.
	 * The thread-space-borders are adjusted along a given axis (which is assumed to be the one,
	 * with the most even particle distribution).
	 * In the end, the time all threads have to wait at their barriers should be reduced significantly,
	 * because all of them reach it in a smaller time interval.
	 *
	 * Call this method only once in a while (every 10000 calculation loops).
	 *
	 * @param domain - a reference to the LCDomain
	 * @param threads - the number of threads - which are active duringt the actual calulation
	 *
	 * @return an int Array - which is indicates the optimal border placements.
	 */
	static void optimizeThreadSpace(LCDomain& domain, int threads, int parallelDomain);

	/**
	 * determines the maximum loops, which the algorithm is allowed to do.
	 */
	static const int OPT_LOOPS = 20;

	/**
	 * Each thread can ask for its cells to compute.
	 */
	static std::vector<ParticleContainer*>* getComputingSpace(int threadNum);


private:
	/**
	 * some helper function
	 * returns the border which has the largest gradient.
	 * The Maximum of second derive (in a discrete way)
	 */
	static int computeLargestGradient(int** input, int size, int* loops);

	/**
	 * contains the cells for each thread
	 */
	static std::vector<ParticleContainer*>* threadContainer;

};

#endif /* DYNAMICTHREADMNGR_H_ */
