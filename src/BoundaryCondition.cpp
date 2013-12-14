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

BoundaryCondition::BoundaryCondition() {
	// TODO Auto-generated constructor stub

	boundarytype[0] = 2;	
	boundarytype[1] = 2;
	boundarytype[2] = 1;
	boundarytype[3] = 1;
	boundarytype[4] = 1;
	boundarytype[5] = 2;
}

BoundaryCondition::~BoundaryCondition() {
	// TODO Auto-generated destructor stub


}

BoundaryCondition::BoundaryCondition(LCDomain* linkedCell_, std::vector<int> domainSize) {
//TODO im not called
	linkedCell = linkedCell_;

	for(int i = 0; i<3; i++){
		this->domainSize[i] = domainSize[i];
	}

	//boundarytype = new int[6];
	

	
	
}


void BoundaryCondition::applyOutflow(ParticleContainer* pc) {
	Particle* p;
	int j = 0;
	while((p = pc->nextParticle(&j)) != NULL){
		linkedCell->deleteParticle(p);
		pc->deleteParticle(p,true);
	}
	std::cout << "DELETE";exit(0);
}
void BoundaryCondition::applyReflecting(ParticleContainer* pc, int axis, bool zero) {
	Particle* p;
	int j = 0;
	while((p = pc->nextParticle(&j)) != NULL){
		Particle* counterP = new Particle(*p);

		double distance = pow(p->getSigma(), 1/6);
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

		}
	}

}

void BoundaryCondition::applySwitch(int type, std::vector<int>& pos, int axis, bool zero) {
	ParticleContainer* pc = linkedCell->getCellAt(pos);

	if(type == 0) {
		for(int i = 0; i < 6; i++) {
			std::cout << i<< " "<<boundarytype[i]<<"\n";
		}

		exit(0);

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

void BoundaryCondition::setLCDomain(LCDomain* linkedCell_) {
	std::cerr<<"try";
	linkedCell = linkedCell_;
	std::cout << &linkedCell<<"\n";
}

LCDomain* BoundaryCondition::getLCDomain(){
	return linkedCell;
}

void BoundaryCondition::setDomainSize(std::vector<int>& domainSize) {
	std:: cout << "LCD: "<<domainSize[2]<<"\n";	
	this->domainSize = domainSize;
}

void BoundaryCondition::setBoundaryType(std::string boundaryType) {
	this->boundaryType = boundaryType;
}

void BoundaryCondition::setPosition(std::string position) {
	this->position = position;
}

void BoundaryCondition::setEpsilon(double epsilon) {
	this->epsilon = epsilon;
}

void BoundaryCondition::setSigma(double sigma) {
	this->sigma = sigma;
}

void BoundaryCondition::setDimension(int dim) {
	this->dimension = dim;
}
void OutflowBoundary::applyBoundaryCondition(int* noOfParticles){
	LOG4CXX_TRACE(loggerBoundaryCondition, "Applying OutflowBoundaryCondition");
	ParticleContainer** pcArray = linkedCell->getCells();
	int size = linkedCell->getNumberOfCells();
	for(int i = 0;i < size;i++){
		Particle* p;
		int j=0;
		while((p = pcArray[i]->nextParticle(&j)) != NULL){
			if(position.compare("right")==0){
				if(p->getX()[0]>domainSize[0]){
					pcArray[i]->deleteParticle(p,true);
					*noOfParticles= *noOfParticles-1;
					std::cerr<<"DELETE\n";
				}
			}else if(position.compare("left")==0){
				if(p->getX()[0]<0){
					pcArray[i]->deleteParticle(p,true);
					*noOfParticles= *noOfParticles-1;
				}
			}else if(position.compare("top")==0){
				if(p->getX()[1]>domainSize[1]){
					pcArray[i]->deleteParticle(p,true);
					*noOfParticles= *noOfParticles-1;
				}
			}else if(position.compare("bottom")==0){
				if(p->getX()[1]<0){
					linkedCell->deleteParticle(p);
					pcArray[i]->deleteParticle(p,true);
					*noOfParticles= *noOfParticles-1;
					std::cerr<<"DELETE\n";

				}
			}else if(position.compare("front")==0){
				if(p->getX()[2]>domainSize[2]){
					pcArray[i]->deleteParticle(p,true);
					*noOfParticles= *noOfParticles-1;
				}
			}else if(position.compare("back")==0){
				if(p->getX()[2]<0){
					pcArray[i]->deleteParticle(p,true);
					*noOfParticles= *noOfParticles-1;
				}
			}else{
				LOG4CXX_FATAL(loggerBoundaryCondition, "Wrong Input for Position in Outflow. Input: " << position);
			}
		}
	}
}

void ReflectingBoundary::applyBoundaryCondition(int* noOfParticles) {
	LOG4CXX_TRACE(loggerBoundaryCondition, "Applying ReflectionBoundaryCondition");
	ParticleContainer** pcArray = linkedCell->getCells();
	int size = linkedCell->getNumberOfCells();
	double maxDistance = pow(sigma, 1/6);
	for(int i = 0;i < size;i++){
		Particle* p;
		int j=0;
		while((p = pcArray[i]->nextParticle(&j)) != NULL){
			//Check Difference for x-direction
			//Check if the Particle p is close to the left boundary of the domain
			if(position.compare("left")==0){
				if((p->getX()[0]<maxDistance)&&(p->getX()[0]>0)){
					//std::cout << "Reflection in y" << std::endl;
					applyForce(p, 0, true);
				}
			//Else check if the Particle p is close to the right boundary of the domain
			}else if(position.compare("right")==0){
				if((p->getX()[0]>(domainSize[0]-maxDistance))&&(p->getX()[0]<domainSize[0])){
				//std::cout << "Reflection in y 2" << std::endl;
				applyForce(p, 0, false);
				}
			}
			//Check Difference for y-direction
			//Check if the Particle p is close to the bottom boundary of the domain
			if(position.compare("bottom")==0){
				if((p->getX()[1]<maxDistance)&&(p->getX()[1]>0)){
					//std::cout << "Reflection in x" << std::endl;
					applyForce(p, 1, true);
				}
				//Else check if the Particle p is close to the top boundary of the domain
			}else if(position.compare("top")==0){
				if((p->getX()[1]>(domainSize[1]-maxDistance))&&(p->getX()[1]<domainSize[1])){
					//std::cout << "Reflection in x 2" << std::endl;
					applyForce(p, 1, false);
				}
			}
			//Check Difference for z-direction
			//Check if the Particle p is close to the front boundary of the domain
			if(position.compare("back")==0){
				if((p->getX()[2]<maxDistance)&&(p->getX()[2]>0)){
					//std::cout << "Reflection in z" << std::endl;
					applyForce(p, 2, true);
			}
			//Else check if the Particle p is close to the back boundary of the domain
			}else if(position.compare("front")==0){
				if((p->getX()[2]>(domainSize[2]-maxDistance))&&(p->getX()[2]<domainSize[2])){
				//std::cout << "Reflection in z 2" << std::endl;
				applyForce(p, 2, false);
				}
			}
		}
	}
}

void ReflectingBoundary::applyForce(Particle* p, int axis, bool orientation){
	Particle* counterP = new Particle(*p);
	utils::Vector<double, 3> oldX = counterP->getX();
	if(orientation){
		oldX[axis] = 0;
	}else{
		oldX[axis] = domainSize[axis];
	}
	counterP->setX(oldX);
	Sheet3Calc::calculateSingleForce(p,counterP);
	delete counterP;
}

void PeriodicBoundary::applyBoundaryCondition(int* noOfParticles) {
	LOG4CXX_TRACE(loggerBoundaryCondition, "Applying PeriodicBoundaryCondition");
	ParticleContainer** pcArray = linkedCell->getCells();
	int size = linkedCell->getNumberOfCells();
	for(int i = 0;i < size;i++){
		Particle* p;
		int j=0;
		while((p = pcArray[i]->nextParticle(&j)) != NULL){
			if(position.compare("right")==0){
				if(p->getX()[0]>domainSize[0]){
					utils::Vector<double, 3> oldX = p->getX();
					oldX[0] = oldX[0]-domainSize[0];
					p->setX(oldX);
				}
			}else if(position.compare("left")==0){
				if(p->getX()[0]<0){
					utils::Vector<double, 3> oldX = p->getX();
					oldX[0] = oldX[0]+domainSize[0];
					p->setX(oldX);
				}
			}else if(position.compare("top")==0){
				if(p->getX()[1]>domainSize[1]){
					utils::Vector<double, 3> oldX = p->getX();
					oldX[1] = oldX[1]-domainSize[1];
					p->setX(oldX);
				}
			}else if(position.compare("bottom")==0){
				if(p->getX()[1]<0){
					utils::Vector<double, 3> oldX = p->getX();
					oldX[1] = oldX[1]+domainSize[1];
					p->setX(oldX);
				}
			}else if(position.compare("front")==0){
				if(p->getX()[2]>domainSize[2]){
					utils::Vector<double, 3> oldX = p->getX();
					oldX[2] = oldX[2]-domainSize[2];
					p->setX(oldX);
				}
			}else if(position.compare("back")==0){
				if(p->getX()[2]<0){
					utils::Vector<double, 3> oldX = p->getX();
					oldX[2] = oldX[2]+domainSize[2];
					p->setX(oldX);
				}
			}else{
				LOG4CXX_FATAL(loggerBoundaryCondition, "Wrong Input for Position in Peridiodic. Input: " << position);
			}
		}
	}
}
