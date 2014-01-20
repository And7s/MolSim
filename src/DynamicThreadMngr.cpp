/*
 * DynamicThreadMngr.cpp
 *
 *  Created on: Jan 15, 2014
 *      Author: paul
 */

#include "DynamicThreadMngr.h"



DynamicThreadMngr::DynamicThreadMngr() {
	// TODO Auto-generated constructor stub

}

DynamicThreadMngr::~DynamicThreadMngr() {
	// TODO Auto-generated destructor stub
}

/**
 * Logger
 */
LoggerPtr loggerDTM(Logger::getLogger( "main.dynamicThreadMngr"));

std::vector<ParticleContainer*>* DynamicThreadMngr::threadContainer;

void DynamicThreadMngr::optimizeThreadSpace(LCDomain& domain, int threads, int particleSize) {
	bool foundOpt = false;
	int totalThreads = threads;
	int* result = new int[totalThreads-1];
	int totalColumns = domain.getBounds()[0];

	//setup
	int i;

	//for(i = 1; i < totalThreads; i++){
	//	result[i-1] = (totalColumns / totalThreads) * i;
	//}
	
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
	LOG4CXX_INFO(loggerDTM,"Adjusting thread workload...");
	for(loops = 0; loops < totalThreads; loops++){
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
			std::cout << "LB: " << leftborder << " RB: " << rightborder << std::endl;
			for(x = leftborder; x < rightborder; x++){
				for(y = 0; y < domain.getBounds()[1]; y++){
					for(z = 0; z < domain.getBounds()[2]; z++){
						std::vector<int> position (3);
						position[0] = x;
						position[1] = y;
						position[2] = z;
						pc = domain.getCellAt(position);
						count[i] += pc->getLength();
					}
				}
			}
			std::cout << "Stats: space [" << i << "] has " << count[i] << std::endl;
		}
		int gradIndex = DynamicThreadMngr::computeLargestGradient(&count,totalThreads);
		int currentGradient;
		std::cout << "gradIndex: " << gradIndex << std::endl;
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
			for(y = 0; y < domain.getBounds()[1]; y++){
				for(z = 0; z < domain.getBounds()[2]; z++){
					std::vector<int> position (3);
					position[0] = x;
					position[1] = y;
					position[2] = z;
					tempVec.push_back(domain.getCellAt(position));
				}
			}
		}
		threadContainer[i] = tempVec;
		std::cout << threadContainer[i].size() << std::endl;
	}
	exit(0);
}

std::vector<ParticleContainer*>* DynamicThreadMngr::getComputingSpace(
		int threadNum) {
	return &(threadContainer[threadNum]);
}

int DynamicThreadMngr::computeLargestGradient(int** input, int size) {
	//int* gradients = new int[size-1];
	int i;
	int maxValue = -1;
	int maxIndex = -1;
	for(i = 0; i < size-1; i++){
		if((*input)[i]==0||(*input)[i+1]==0){
			maxIndex = i;
			break;
		}else if(abs((*input)[i+1] - (*input)[i]) >= maxValue){
			maxValue = abs((*input)[i+1] - (*input)[i]);
			maxIndex = i;
		}
	}
	return maxIndex;
}

