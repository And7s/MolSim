/*
 * BoundaryCondition.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: friedrich
 */

#include "BoundaryCondition.h"

BoundaryCondition::BoundaryCondition() {
	// TODO Auto-generated constructor stub

}

BoundaryCondition::~BoundaryCondition() {
	// TODO Auto-generated destructor stub
}

BoundaryCondition::BoundaryCondition(LinkedCell*& linkedCell, utils::Vector<double, 3> domainSize) {
	this->linkedCell = linkedCell;
	for(int i = 0; i<3; i++){
		this->domainSize[i] = domainSize[i];
	}
}

void BoundaryCondition::setLinkedCell(LinkedCell*& linkedCell) {
	this->linkedCell = linkedCell;
}

LinkedCell*& BoundaryCondition::getLinkedCell(){
	return linkedCell;
}

Calculation*& BoundaryCondition::getCalculation(){
	return calculation;
}

void BoundaryCondition::setCalculation(Calculation*& calculation) {
	this->calculation = calculation;
}

utils::Vector<double, 3> BoundaryCondition::getDomainSize(){
	return domainSize;
}

void OutflowBoundary::applyBoundaryCondition(){
	for(int i = 0;i < linkedCell->getParticleListArray()->size();i++){
		std::list<Particle>::iterator iterator = linkedCell->getParticleListArray()[i].begin();
		while(iterator != linkedCell->getParticleListArray()[i].end()){
			Particle& p = *iterator;
			utils::Vector<double, 3> difference =  domainSize-p.getX();
			if(difference[0]<0||difference[0]>domainSize[0]){
				delete& p;
			}else if(difference[1]<0||difference[1]>domainSize[1]){
				delete& p;
			}else if(difference[2]<0||difference[2]>domainSize[2]){
				delete& p;
			}
			iterator++;
		}
	}
}

void ReflectingBoundary::applyBoundaryCondition() {
	double maxDistance = pow(sigma, 1/6);
	for(int i = 0;i < linkedCell->getParticleListArray()->size();i++){
		std::list<Particle>::iterator iterator = linkedCell->getParticleListArray()[i].begin();
		while(iterator != linkedCell->getParticleListArray()[i].end()){
			Particle& p = *iterator;
			utils::Vector<double, 3> difference =  domainSize-p.getX();
			//Check Difference for x-direction
			//Check if the Particle p is close to the right boundary of the domain
			if((difference[0]<maxDistance)&&(difference[0]>0)){
				applyForce(p, 0, 1);
			//Else check if the Particle p is close to the left boundary of the domain
			}else if((difference[0]<0)&&(domainSize[0]-abs(difference[0])<maxDistance)){
				applyForce(p, 0, 0);
			}
			//Check Difference for y-direction
			//Check if the Particle p is close to the bottom boundary of the domain
			if((difference[1]<maxDistance)&&(difference[1]>0)){
				applyForce(p, 1, 1);
			//Else check if the Particle p is close to the top boundary of the domain
			}else if((difference[1]<0)&&(domainSize[1]-abs(difference[1])<maxDistance)){
				applyForce(p, 1, 0);
			}
			//Check Difference for z-direction
			//Check if the Particle p is close to the front boundary of the domain
			if((difference[2]<maxDistance)&&(difference[2]>0)){
				applyForce(p, 2, 1);
			//Else check if the Particle p is close to the back boundary of the domain
			}else if((difference[2]<0)&&(domainSize[2]-abs(difference[2])<maxDistance)){
				applyForce(p, 2, 0);
			}
			iterator++;
		}
	}
}

void ReflectingBoundary::applyForce(Particle& p, int axis, bool orientation){
	Particle* counterP = new Particle(p);
	if(orientation){
		counterP->getX()[axis] = domainSize[axis];
	}else{
		counterP->getX()[axis] = 0;
	}
	Particle** pa = new Particle*[2];
	pa[0] = &p;
	pa[1] = counterP;
	ParticleContainer pc(2);
	pc.setParticles(pa);
	calculation->setParticleContainer(pc);
	calculation->calculateForce();
}
