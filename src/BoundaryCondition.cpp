/*
 * BoundaryCondition.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: friedrich
 */

#include "BoundaryCondition.h"

/**
 * Logger
 */
LoggerPtr loggerBoundaryCondition(Logger::getLogger( "main.boundary"));



BoundaryCondition::~BoundaryCondition() {
	// TODO Auto-generated destructor stub


}

BoundaryCondition::BoundaryCondition(LCDomain* linkedCell_, std::vector<int> domainSize_, int dimension_, auto_ptr<input_t>& inp) {

	linkedCell = linkedCell_;
	
	domainSize = domainSize_;

	dimension = dimension_;
	//boundarytype = new int[6];
	
	boundarytype[0] = inp->boundaryCondition().left();	
	boundarytype[1] = inp->boundaryCondition().right();
	boundarytype[2] = inp->boundaryCondition().bottom();
	boundarytype[3] = inp->boundaryCondition().top();
	boundarytype[4] = inp->boundaryCondition().front();
	boundarytype[5] = inp->boundaryCondition().back();
	
	
}	

void BoundaryCondition::applyOutflow(ParticleContainer* pc) {
	Particle* p;
	int j = 0;
	while((p = pc->nextParticle(&j)) != NULL){
		linkedCell->deleteParticle(p);
		pc->deleteParticle(p,true);
	}
}
void BoundaryCondition::applyReflecting(ParticleContainer* pc, int axis, bool zero) {
	Particle* p;
	int j = 0;
	while((p = pc->nextParticle(&j)) != NULL){
		Particle* counterP = new Particle(*p);

		double distance = pow(p->getSigma(), 1/6.0);
		utils::Vector<double, 3> oldX = counterP->getX();
		if(zero){
			oldX[axis] = -distance;
		}else{
			oldX[axis] = domainSize[axis]*linkedCell->getCutOffRadius()+distance;
		}
		counterP->setX(oldX);

		Sheet3Calc::calculateSingleForce(p,counterP);

		delete counterP;
	}
}
void BoundaryCondition::applyPeriodic(ParticleContainer* pc, ParticleContainer* pc2, int axis, bool zero) {
	Particle* p;
	int j = 0;
	while((p = pc->nextParticle(&j)) != NULL){
		if(p->getType() == -1) {
			//im a copy (delete?)
		}else {
			//im an original, move me to the other side
			utils::Vector<double, 3> pos = p->getX();
			if(zero) {
				pos[axis] += domainSize[axis]*linkedCell->getCutOffRadius();
			}else {
				pos[axis] -= domainSize[axis]*linkedCell->getCutOffRadius();
			}

			p->setX(pos);

		}
	}
	pc->clearParticles();

	while((p = pc2->nextParticle(&j)) != NULL){
		if(p->getType() == -1) {
			//im a copy (delete?)
		}else {
			Particle* pcopy = new Particle(*p);

			utils::Vector<double, 3> pos = pcopy->getX();
			if(zero) {
				pos[axis] -= domainSize[axis]*linkedCell->getCutOffRadius();
			}else {
				pos[axis] += domainSize[axis]*linkedCell->getCutOffRadius();
			}
			
			pcopy->setX(pos);
			pcopy->setType(-1);
			pc->setParticle(pcopy);
			linkedCell->addHaloParticle(pcopy);

		}
	}

}

void BoundaryCondition::applySwitch(int type, std::vector<int>& pos, int axis, bool zero) {
	ParticleContainer* pc = linkedCell->getCellAt(pos);

	if(type == 0) {
		applyOutflow(pc);
	}else if(type == 1) {
		applyReflecting(pc, axis, zero);
	}else if(type == 2) {
		
		std::vector<int> pos2 (3,0);
		for(int i = 0; i < 3; i++) pos2[i] = pos[i];
		if(zero) {
			pos2[axis]+= domainSize[axis];
		}else {
			pos2[axis] -= domainSize[axis];
		}

		ParticleContainer* pc2 = linkedCell->getCellAt(pos2);
			applyPeriodic(pc, pc2, axis, zero);
	
	}else {
		LOG4CXX_FATAL(loggerBoundaryCondition, "undefined BoundaryCondition called");	
	}
}
void BoundaryCondition::apply() {
	int c = 0;

	std::vector<int> pos (3,0);
	for(pos[0] = 0; pos[0] < domainSize[0]+2; pos[0]++) {
		for(pos[1] = 0; pos[1] < domainSize[1]+2; pos[1]++) {
			for(pos[2] = 0; pos[2] < domainSize[2]+2 && (pos[2] == 0 || dimension > 2); pos[2]++) {
				if(pos[0] == 0 ){
					//check left
					//std::cout << "Check left\n";
					c++;
					applySwitch(boundarytype[0], pos, 0, true);
				}
				if(pos[0] == domainSize[0]+1) {
					//check right
					c++;
					applySwitch(boundarytype[1], pos, 0, false);
				}

				if(pos[1] == 0 ){
					//check bottom
					c++;
					applySwitch(boundarytype[2], pos, 1, true);
				}
				if(pos[1] == domainSize[1]+1) {
					//check top
					c++;
					applySwitch(boundarytype[3], pos, 1, false);
				}
				if(dimension == 3) {
					if(pos[2] == 0 ){
						//check front
						c++;
						applySwitch(boundarytype[4], pos, 2, true);
					}
					if(pos[2] == domainSize[2]+1) {
						//check top
						c++;
						applySwitch(boundarytype[5], pos, 2, false);
					}
				}
			}
		}
	}
	//std::cout << "Boundary Checks did: "<<c<<"\n";
}


