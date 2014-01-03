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
		std::cerr << "apply outflow, shouldn happen";
		linkedCell->deleteParticle(p);
		pc->deleteParticle(p,true);
	}
}
void BoundaryCondition::applyReflecting(ParticleContainer* pc, int axis, bool zero) {
	//std::cerr << "Apply reflecting";

	Particle* p;
	int j = 0;
	while((p = pc->nextParticle(&j)) != NULL){
		if(p->getType() != -1) {
			Particle* counterP = new Particle(*p);

			double distance = pow(p->getSigma(), 1/6.0);
			
			utils::Vector<double, 3> oldX = counterP->getX();
			//if(axis == 2 && !zero) std::cout << "reflect at "<<oldX[axis]<<" "<< p->getUid()<<"\n";
			if(zero){
				if(oldX[axis] <= -distance) {
					std::cerr << "Instability : too far \n"<<*p<<"\n";
					exit(0);

				}else {
					oldX[axis] = -distance;
				}
				

			}else{
				if(oldX[axis] >= domainSize[axis]*linkedCell->getCutOffRadius()+distance) {
					std::cout << "Distance "<<domainSize[axis]*linkedCell->getCutOffRadius()+distance<<" "<<*p<<"\n";
					std::cout << "Reflect "<< p->getUid()<<"\n";
					std::cerr << "Instability : too far2 \n"<<*p<<"\n";
					exit(0);

				}else {
					oldX[axis] = domainSize[axis]*linkedCell->getCutOffRadius()+distance;
				}

				
			}

//I AM AN HACK DONT USE ME IM EVIL
//JUST FOR DESTING AND CAUS IM DESPERATE
utils::Vector<double, 3> oldv = p->getV();
oldv = oldv * 0.0;
//p->setV(oldv);
			counterP->setX(oldX);

			Sheet3Calc::calculateSingleForce(p,counterP);
			//Sheet3Calc::calculateSingleForce(p,counterP);

			delete counterP;
		}else {
			//std::cerr << "typ "<<p->getType();
		}
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
			//std::cerr << "From "<< pos[axis];
			if(zero) {
				pos[axis] += domainSize[axis]*linkedCell->getCutOffRadius();
			}else {
				pos[axis] -= domainSize[axis]*linkedCell->getCutOffRadius();
			}
			pc2->setParticle(p);
			Particle* pcopy = new Particle(*p);

			//std::cerr << " 	periodic move"<< p->getUid()<<" to "<<pos[axis]<<"\n";

		//	std::cerr << "Copy is at "<<pcopy->getX()[axis]<<"\n";
			p->setX(pos);

	
			//AND create a copy of me, becuase im not in the real LCDomain, but in the halo


			

			pcopy->setType(-1);
			pc->setParticle(pcopy);
			linkedCell->addHaloParticle(pcopy);


		}
	}
	pc->clearParticles();

	while((p = pc2->nextParticle(&j)) != NULL){
		/*if(p->getType() == -1) {
			//im a copy (delete?)
		}else {*/
		//Do it for every axis, (mirroring)
			Particle* pcopy = new Particle(*p);

			utils::Vector<double, 3> pos = pcopy->getX();
			if(p->getUid() == 27) {
				//std::cout << "is at: "<<pos<<"\n";
			}
			if(zero) {
				pos[axis] -= domainSize[axis]*linkedCell->getCutOffRadius();
			}else {
				pos[axis] += domainSize[axis]*linkedCell->getCutOffRadius();
			}
			if(p->getUid() == 27) {
			//	std::cerr << "Add Copy of "<< p->getUid()<<" at "<<pos[axis]<< "axis; "<<axis<<"\n";
			}
			pcopy->setX(pos);
			pcopy->setType(-1);
			pc->setParticle(pcopy);
			linkedCell->addHaloParticle(pcopy);

		//}
	}
}

void BoundaryCondition::applySwitch(int type, std::vector<int>& pos, int axis, bool zero, ParticleContainer* pc) {

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
	ParticleContainer* pc;

	#pragma omp parallel for schedule(dynamic) private(pc)
	for(int i = 0; i < domainSize[0]+2; i++) {
		std::vector<int> pos (3,0);
		pos[0] = i;
		for(pos[1] = 0; pos[1] < domainSize[1]+2; pos[1]++) {
			for(pos[2] = 0; pos[2] < domainSize[2]+2 && (pos[2] == 0 || dimension > 2); pos[2]++) {
				if(pos[0] == 0 ){
					//check left

					pc = linkedCell->getCellAt(pos);
					//if(!pc->isempty()) {
						applySwitch(boundarytype[0], pos, 0, true, pc);
					//}
				}
				if(pos[0] == domainSize[0]+1) {
					//check right
					pc = linkedCell->getCellAt(pos);
					//if(!pc->isempty()) {
						applySwitch(boundarytype[1], pos, 0, false, pc);
					//}
				}

				if(pos[1] == 0 ){
					//check bottom
					pc = linkedCell->getCellAt(pos);
					//if(!pc->isempty()) {
						applySwitch(boundarytype[2], pos, 1, true, pc);
					//}
				}
				if(pos[1] == domainSize[1]+1) {
					//check top
					pc = linkedCell->getCellAt(pos);
					//if(!pc->isempty()) {
						applySwitch(boundarytype[3], pos, 1, false, pc);
					//}
				}
				if(dimension == 3) {
					if(pos[2] == 0 ){
						//check front
						pc = linkedCell->getCellAt(pos);
						//if(!pc->isempty()) {
							applySwitch(boundarytype[4], pos, 2, true, pc);
						//}
					}
					if(pos[2] == domainSize[2]+1) {
						//check back

						pc = linkedCell->getCellAt(pos);
						//if(!pc->isempty()) {
							applySwitch(boundarytype[5], pos, 2, false, pc);
						//}
					}
				}
			}
		}
	}
}


