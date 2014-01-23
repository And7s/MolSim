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

BoundaryCondition::BoundaryCondition(LCDomain* linkedCell_, std::vector<int> domainSize_, int dimension_, auto_ptr<input_t>& inp, int* length_) {

	linkedCell = linkedCell_;
	
	domainSize = domainSize_;

	dimension = dimension_;
	
	boundarytype[0] = inp->boundaryCondition().left();	
	boundarytype[1] = inp->boundaryCondition().right();
	boundarytype[2] = inp->boundaryCondition().bottom();
	boundarytype[3] = inp->boundaryCondition().top();
	boundarytype[4] = inp->boundaryCondition().front();
	boundarytype[5] = inp->boundaryCondition().back();
	
	length = length_;

}	

void BoundaryCondition::applyOutflow(ParticleContainer* pc) {
	Particle* p;
	int j = 0;
	while((p = pc->nextParticle(&j)) != NULL){
		if(p->getType() != -1) {
			std::cerr << "apply outflow";
			linkedCell->deleteParticle(p);
			//pc->deleteParticle(p,true);
			(*length)=(*length) - 1;
			p->setType(-1);
		}
	}
}
void BoundaryCondition::applyReflecting(ParticleContainer* pc, int axis, bool zero) {
	Particle* p;
	int j = 0;
	while((p = pc->nextParticle(&j)) != NULL){
		if(p->getType() != -1) {
			Particle* counterP = new Particle(*p);

			double distance = pow(p->getSigma(), 1/6.0);
			
			utils::Vector<double, 3> oldX = counterP->getX();

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

			counterP->setX(oldX);

			Calculation::calculateSingleForce(p,counterP);
			delete counterP;
		}
	}
}
void BoundaryCondition::applyPeriodic(ParticleContainer* pc, ParticleContainer* pc2, int axis, bool zero, std::vector<int>& posCell) {
	if(posCell[0] == 0 && posCell[2] == 0 && posCell[1] == 1) {
		//std:cout << "Called from axis "<<axis<<" "<< posCell[1]<<"\n";
		pc = linkedCell->getCellAt(posCell);
	}
	Particle* p;
	int j = 0;
	while((p = pc->nextParticle(&j)) != NULL){

		//std::cout << "\napply Periodic"<<axis;
		if(p->getType() == -1) {
		}else {
			//im an original, move me to the other side
			utils::Vector<double, 3> pos = p->getX();
			//std::cout << pos[0]<< " "<<pos[1] <<" "<<pos[2]<< "axis" <<axis <"\n";
		//	std::cout << "other side";
//std::cout << "Direct Copy "<< pos[0]<< " "<<pos[1] <<" "<<pos[2]<<"\n";
			
			if(zero) {
				pos[axis] += domainSize[axis]*linkedCell->getCutOffRadius();
			}else {
				pos[axis] -= domainSize[axis]*linkedCell->getCutOffRadius();
			}


			//std::cout << "move to "<< pos[0]<< " "<<pos[1] <<" "<<pos[2]<<"\n";
			//pc2->setParticle(p);
			Particle* pcopy = new Particle(*p);

			p->setX(pos);	
			pcopy->setType(-1);
			//pc->setParticle(pcopy);
			linkedCell->addHaloParticle(pcopy);

			for(int i = 0; i < 3; i++) {
				if(i != axis) {
					if(posCell[i] == 0 || posCell[i] == domainSize[i]+1) {
						//std::cout << "Special handling at "<<posCell[0]<<" "<<posCell[1]<< " "<<posCell[2]<<"\n";
						if(boundarytype[i*2] == 2) {
							Particle* pcopy2 = new Particle(*pcopy);

							utils::Vector<double, 3> pos2 = pcopy2->getX();
							if(posCell[i] == 0) {
								pos[i] += domainSize[i]*linkedCell->getCutOffRadius();
								pos2[i] += domainSize[i]*linkedCell->getCutOffRadius();
							}else {
								pos[i] -= domainSize[i]*linkedCell->getCutOffRadius();
								pos2[i] -= domainSize[i]*linkedCell->getCutOffRadius();
							}
							p->setX(pos);
							//std::cout << "move to "<< pos[0]<< " "<<pos[1] <<" "<<pos[2]<<"\n";
			
							pcopy2->setX(pos2);
							//std::cout << "Copy at pushing "<< pos2[0]<< " "<<pos2[1] <<" "<<pos2[2]<<"\n";
							//pcopy2->setType(-1);
							//pc->setParticle(pcopy2);
							linkedCell->addHaloParticle(pcopy2);

							Particle* pcopy3 = new Particle(*p);

							pos2 = pcopy3->getX();
							if(posCell[i] == 0) {
								pos2[i] -= domainSize[i]*linkedCell->getCutOffRadius();
							}else {
								pos2[i] += domainSize[i]*linkedCell->getCutOffRadius();
							}

							pcopy3->setX(pos2);
							//std::cout << "Copy at pushing "<< pos2[0]<< " "<<pos2[1] <<" "<<pos2[2]<<"\n";
							//pcopy2->setType(-1);
							//pc->setParticle(pcopy2);
							linkedCell->addHaloParticle(pcopy3);
							
						}
					}
				}
			} 

		}
	}
	pc->clearParticles();
	j = 0;	
	while((p = pc2->nextParticle(&j)) != NULL){
		
		if(p->getType() != -1) {
			//std::cout << "Copy from pc2";
			Particle* pcopy = new Particle(*p);

			utils::Vector<double, 3> pos = pcopy->getX();
			
			if(zero) {
				pos[axis] -= domainSize[axis]*linkedCell->getCutOffRadius();
			}else {
				pos[axis] += domainSize[axis]*linkedCell->getCutOffRadius();
			}

			pcopy->setX(pos);
			pcopy->setType(-1);
			//pc->setParticle(pcopy);
			linkedCell->addHaloParticle(pcopy);


			
		}
	}

	for(int i = 0; i < 3; i++) {
		if(i != axis) {
			if(posCell[i] == 0 || posCell[i] == domainSize[i]+1) {
				if(boundarytype[i*2] == 2) {
					//std::cout << "extra handling needed\n";
					//std::cout << posCell[0] << " "<<posCell[1] << " "<<posCell[2]<<"\n";
					if(i < axis) {
						//std::cout << "not again\n";
					}else {
						std::vector<int> tmp (3,0);
						for(int k = 0; k < 3; k++ ) tmp[k] = posCell[k];
						if(posCell[i] == 0) {
							tmp[i] += domainSize[i];
						}else {
							tmp[i] -= domainSize[i];
						}
						if(zero) {
							tmp[axis] += domainSize[axis];
						}else {
							tmp[axis] -=domainSize[axis];
						}
						//std::cout << "take from "<<tmp[0]<<" "<<tmp[1]<< " "<<tmp[2]<<" I: "<<i<<" axis: " <<axis<<"\n";
						pc2 = linkedCell->getCellAt(tmp);
						j = 0;
							j = 0;	
							while((p = pc2->nextParticle(&j)) != NULL){
								
								if(p->getType() != -1) {
									//std::cout << "Copy from double";
									Particle* pcopy = new Particle(*p);

									utils::Vector<double, 3> pos = pcopy->getX();
									
									if(zero) {
										pos[axis] -= domainSize[axis]*linkedCell->getCutOffRadius();
									}else {
										pos[axis] += domainSize[axis]*linkedCell->getCutOffRadius();
									}

						if(posCell[i] == 0) {
							pos[i] -= domainSize[i]*linkedCell->getCutOffRadius();
						}else {
							pos[i] += domainSize[i]*linkedCell->getCutOffRadius();
						}
						//std::cout << "set Copy to  "<< pos[0]<< " "<<pos[1] <<" "<<pos[2]<<"\n";
									pcopy->setX(pos);
									pcopy->setType(-1);
									//pc->setParticle(pcopy);
									linkedCell->addHaloParticle(pcopy);


									
								}
							}
						}
				}
			}
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
		//std::cout << "Apply periodic";
		std::vector<int> pos2 (3,0);
		for(int i = 0; i < 3; i++) pos2[i] = pos[i];
		if(zero) {
			pos2[axis]+= domainSize[axis];
		}else {
			pos2[axis] -= domainSize[axis];
		}
if(pos[0] == 0 && pos[2] == 0) {
		//std:cout << "Called from axis "<<axis<<"\n";
	}
		ParticleContainer* pc2 = linkedCell->getCellAt(pos2);
			applyPeriodic(pc, pc2, axis, zero, pos);
	
	}else {
		LOG4CXX_FATAL(loggerBoundaryCondition, "undefined BoundaryCondition called");	
	}
	
}
void BoundaryCondition::apply() {
	ParticleContainer* pc;
	//std::cout << "end appöy\n";
	//this leads for some unknown reason to a segmentation fault,
	//propably, because the individual handlers interver with each other (periodic copies and outflow deletes -> solution needs design dicussion)
	//#pragma omp parallel for schedule(dynamic) private(pc)
	for(int i = 0; i < domainSize[0]+2; i++) {
		std::vector<int> pos (3,0);
		pos[0] = i;
		for(pos[1] = 0; pos[1] < domainSize[1]+2; pos[1]++) {
			for(pos[2] = 0; pos[2] < domainSize[2]+2 && (pos[2] == 0 || dimension > 2); pos[2]++) {
				if(pos[0] == 0 ){
					//check left

					applySwitch(boundarytype[0], pos, 0, true);
				}
				if(pos[0] == domainSize[0]+1) {
					//check right
					applySwitch(boundarytype[1], pos, 0, false);

				}
				if(pos[1] == 0 ){
					//check bottom

					applySwitch(boundarytype[2], pos, 1, true);
				}
				if(pos[1] == domainSize[1]+1) {
					//check top
					applySwitch(boundarytype[3], pos, 1, false);

				}
				if(dimension == 3) {

					if(pos[2] == 0 ){
						//std::cout << "Called"<<pos[0];
						//check front
						if(pos[0] == 0 && pos[2] == 0) {
		//std:cout << "called sth \n";
	}
						applySwitch(boundarytype[4], pos, 2, true);
					}
					if(pos[2] == domainSize[2]+1) {
						//check back
						applySwitch(boundarytype[5], pos, 2, false);
					}
				}
			}
		}
	}
}
