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

}

BoundaryCondition::~BoundaryCondition() {
	// TODO Auto-generated destructor stub
}

BoundaryCondition::BoundaryCondition(LCDomain& linkedCell, std::vector<int> domainSize) {
	this->linkedCell = linkedCell;
	for(int i = 0; i<3; i++){
		this->domainSize[i] = domainSize[i];
	}
}

void BoundaryCondition::setLCDomain(LCDomain& linkedCell) {
	this->linkedCell = linkedCell;
}

LCDomain& BoundaryCondition::getLCDomain(){
	return linkedCell;
}

void BoundaryCondition::setDomainSize(std::vector<int>& domainSize) {
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

void OutflowBoundary::applyBoundaryCondition(int* noOfParticles){
	LOG4CXX_TRACE(loggerBoundaryCondition, "Applying OutflowBoundaryCondition");
	ParticleContainer** pcArray = linkedCell.getCells();
	int size = linkedCell.getNumberOfCells();
	for(int i = 0;i < size;i++){
		Particle* p;
		int j=0;
		while((p = pcArray[i]->nextParticle(&j)) != NULL){
			if(position.compare("right")==0){
				if(p->getX()[0]>domainSize[0]){
					pcArray[i]->deleteParticle(p,true);
					*noOfParticles= *noOfParticles-1;
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
					pcArray[i]->deleteParticle(p,true);
					*noOfParticles= *noOfParticles-1;
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
	ParticleContainer** pcArray = linkedCell.getCells();
	int size = linkedCell.getNumberOfCells();
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
	Sheet3Calc::calculateSingleForce(p,counterP,sigma,epsilon);
	delete counterP;
}

void PeriodicBoundary::applyBoundaryCondition(int* noOfParticles) {
	LOG4CXX_TRACE(loggerBoundaryCondition, "Applying PeriodicBoundaryCondition");
	ParticleContainer** pcArray = linkedCell.getCells();
	int size = linkedCell.getNumberOfCells();
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
