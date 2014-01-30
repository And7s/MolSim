/*
 * DynamicThreadMngr.cpp
 *
 *  Created on: Jan 15, 2014
 *      Author: paul
 */

#include "DynamicThreadMngr.h"

/**
 * Logger
 */
LoggerPtr loggerDTM(Logger::getLogger( "main.dynamicThreadMngr"));

std::vector<ParticleContainer*>* DynamicThreadMngr::threadContainer;

void DynamicThreadMngr::optimizeThreadSpace(LCDomain& domain, int threads, int parallelDomain) {
	bool foundOpt = false;
	int totalThreads = threads;
	int* result = new int[totalThreads-1];
	//setup
	int i, h;
	i = 0;
	LOG4CXX_INFO(loggerDTM, "parallelDomain: " << parallelDomain);

	int maxSize = domain.getBounds()[0];
	for(h = 1; h < 3; ++h){
		if(domain.getBounds()[h]>maxSize){
			maxSize = domain.getBounds()[h];
			i++;
		}
	}
	h = (parallelDomain!=-1) ? parallelDomain : i;
	int totalColumns = domain.getBounds()[h];
	
	///NEW: Balance the array so that every column has about equal size
	int step = ceil(((double)totalColumns)/totalThreads);
	int modulo = totalColumns%totalThreads;
	result[0] = step;
	for(i=1;i<totalThreads-1;i++){
		if(i<modulo){
			result[i] = result[i-1] + step; 
		}else{
			result[i] = result[i-1] + step -1;
		}
	}
	//END NEW	
	int leftborder, rightborder;

	ParticleContainer* pc;

	char lastMoveDirection = 'n'; //r or l
	int lastMoveBorder = -1;
	int lastMoveGradient = -1;

	int loops;
	int* count = new int[totalThreads];
	int x,y,z;
	char dimension[3] = {'x','y','z'};
	LOG4CXX_INFO(loggerDTM,"Adjusting thread workload along the longest Domain: " << dimension[h] << " with Size: " << maxSize);

	for(loops = 0; loops < (totalThreads<OPT_LOOPS ? OPT_LOOPS : totalThreads); loops++){
		//clear count - for some reason necessary even if declared in this loop ..
		for(i = 0; i < totalThreads; i++){
			count[i] = 0;
			if(i > 0){
				leftborder = result[i-1];
			}else{
				leftborder = 0;
			}
			if(i < totalThreads -1){
				rightborder = result[i];
			}else{
				rightborder = totalColumns;	//actually not in domain space - this is fine
			}
			LOG4CXX_TRACE(loggerDTM, "LB: " << leftborder << " RB: " << rightborder);
			for(x = leftborder; x < rightborder; x++){
				for(y = 0; y < domain.getBounds()[(h+1)%3]; y++){
					for(z = 0; z < domain.getBounds()[(h+2)%3]; z++){
						std::vector<int> position (3);
						position[h] = x;
						position[(h+1)%3] = y;
						position[(h+2)%3] = z;
						pc = domain.getCellAt(position);
						count[i] += pc->getLength();
					}
				}
			}
			LOG4CXX_TRACE(loggerDTM, "Stats: space [" << i << "] has " << count[i]);
		}
		int gradIndex = DynamicThreadMngr::computeLargestGradient(&count,totalThreads, &loops);
		int currentGradient;
		LOG4CXX_TRACE(loggerDTM, "gradIndex: " << gradIndex  << " LastMove: "<< lastMoveDirection << "\n____________");
		if((currentGradient = count[gradIndex] - count[gradIndex+1]) < 0){	//means that the left sector has less
																			//position border to the right!
			currentGradient = abs(currentGradient);
			if(gradIndex == lastMoveBorder && lastMoveDirection == 'l'){	//optimum has been found in this or previous loop
				foundOpt = true;
				if(currentGradient > lastMoveGradient){		//determine if optimum was found last loop or now.
					result[gradIndex] ++;					//if so, hop back
				}
				break;
			}
			result[gradIndex] ++;
			lastMoveDirection = 'r';
		}else{
			if(gradIndex == lastMoveBorder && lastMoveDirection == 'r'){
				foundOpt = true;
				if(currentGradient > lastMoveGradient){
					result[gradIndex] --;	//hop back
				}
				break;
			}
			result[gradIndex] --;
			lastMoveDirection = 'l';
		}
		lastMoveBorder = gradIndex;
		lastMoveGradient = currentGradient;
	}
	
	if(foundOpt){
		LOG4CXX_INFO(loggerDTM, "Optimum found! Thread workload balanced");
	}else{
		LOG4CXX_INFO(loggerDTM, "Aborting.. maximum loops exhausted! Thread workload balanced");
	}
	/////TESTPRINT
	LOG4CXX_INFO(loggerDTM, "Final Balance:");
	for(i = 0; i < totalThreads; i++){
		count[i] = 0;
		if(i > 0){
			leftborder = result[i-1];
		}else{
			leftborder = 0;
		}
		if(i < totalThreads -1){
			rightborder = result[i];
		}else{
			rightborder = totalColumns;	//actually not in domain space - this is fine
		}
		LOG4CXX_INFO(loggerDTM, "LB: " << leftborder << " RB: " << rightborder);
		for(x = leftborder; x < rightborder; x++){
			for(y = 0; y < domain.getBounds()[(h+1)%3]; y++){
				for(z = 0; z < domain.getBounds()[(h+2)%3]; z++){
					std::vector<int> position (3);
					position[h] = x;
					position[(h+1)%3] = y;
					position[(h+2)%3] = z;
					pc = domain.getCellAt(position);
					count[i] += pc->getLength();
				}
			}
		}
		LOG4CXX_INFO(loggerDTM, "Stats: space [" << i << "] has " << count[i] << " particles.");
	}
	///////END TEST
	threadContainer = new std::vector<ParticleContainer*>[totalThreads];


	for(i = 0; i < totalThreads; i++){
		std::vector<ParticleContainer*> tempVec;
		if(i > 0){
			leftborder = result[i-1];
		}else{
			leftborder = 0;
		}
		if(i < totalThreads -1){
			rightborder = result[i];
		}else{
			rightborder = totalColumns;	//actually not in domain space - this is fine
		}
		for(x = leftborder; x < rightborder; x++){
			for(y = 0; y < domain.getBounds()[(h+1)%3]; y++){
				for(z = 0; z < domain.getBounds()[(h+2)%3]; z++){
					std::vector<int> position (3);
					position[h] = x;
					position[(h+1)%3] = y;
					position[(h+2)%3] = z;
					tempVec.push_back(domain.getCellAt(position));
				}
			}
		}
		threadContainer[i] = tempVec;
		LOG4CXX_INFO(loggerDTM, "Thread "<<i<<" has "<< threadContainer[i].size()<<" Cells");
	}
}

std::vector<ParticleContainer*>* DynamicThreadMngr::getComputingSpace(
		int threadNum) {
	return &(threadContainer[threadNum]);
}

int DynamicThreadMngr::computeLargestGradient(int** input, int size, int* loops) {
	int i;
	int maxValue = -1;
	int maxIndex = -1;
	for(i = 0; i < size-1; i++){
		if((*input)[i]==0){
			(*loops)--;
			if((*input)[i+1]!=0){
			maxIndex = i;
			break;
			}
		}else if(abs((*input)[i+1] - (*input)[i]) >= maxValue){
			maxValue = abs((*input)[i+1] - (*input)[i]);
			maxIndex = i;
		}
	}
	return maxIndex;
}

