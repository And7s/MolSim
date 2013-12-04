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

Calculation*& BoundaryCondition::getCalculation(){
	return calculation;
}

void BoundaryCondition::setDomainSize(std::vector<int>& domainSize) {
	this->domainSize = domainSize;
}

void BoundaryCondition::setSigma(double sigma) {
	this->sigma = sigma;
}

void BoundaryCondition::setCalculation(Calculation*& calculation) {
	this->calculation = calculation;
}

void OutflowBoundary::applyBoundaryCondition(){
	ParticleContainer** pcArray = linkedCell.getCells();
	int size = linkedCell.getNumberOfCells();
	for(int i = 0;i < size;i++){
		Particle* p;
		while((p = pcArray[i]->nextParticle()) != NULL){
			if((p->getX()[0]<0)||(p->getX()[0]>domainSize[0])){
				std::cout << "Wrong in x direction" << std::endl;
				std::cout << "x: " << p->getX() << std::endl;
				pcArray[i]->deleteParticle(p);
			}else if(p->getX()[1]<0||p->getX()[1]>domainSize[1]){
				std::cout << "Wrong in y direction" << std::endl;
				std::cout << "y: " << p->getX() << std::endl;
				pcArray[i]->deleteParticle(p);
			}else if(p->getX()[2]<0||p->getX()[2]>domainSize[2]){
				std::cout << "Wrong in z direction" << std::endl;
				std::cout << "z: " << p->getX() << std::endl;
				pcArray[i]->deleteParticle(p);
			}
		}
	}
}

void ReflectingBoundary::applyBoundaryCondition() {
	/*LCell** cell = linkedCell->getCells();
	double maxDistance = pow(sigma, 1/6);
	for(int i = 0;i < linkedCell->getNumberOfCells();i++){
		LCell* actCell = cell[i];
		Particle* p = actCell->getNextItem();
		while(p !=NULL){
			//Check Difference for x-direction
			//Check if the Particle p is close to the left boundary of the domain
			if((p->getX()[0]<maxDistance)&&(p->getX()[0]>0)){
				applyForce(p, 0, true);
			//Else check if the Particle p is close to the right boundary of the domain
			}else if((p->getX()[0]>(domainSize[0]-maxDistance))&&(p->getX()[0]<domainSize[0])){
				applyForce(p, 0, false);
			}
			//Check Difference for y-direction
			//Check if the Particle p is close to the top boundary of the domain
			if((p->getX()[1]<maxDistance)&&(p->getX()[1]>0)){
				applyForce(p, 1, true);
			//Else check if the Particle p is close to the bottom boundary of the domain
			}else if((p->getX()[1]>(domainSize[1]-maxDistance))&&(p->getX()[1]<domainSize[1])){
				applyForce(p, 1, false);
			}
			//Check Difference for z-direction
			//Check if the Particle p is close to the front boundary of the domain
			if((p->getX()[2]<maxDistance)&&(p->getX()[2]>0)){
				applyForce(p, 2, true);
			//Else check if the Particle p is close to the back boundary of the domain
			}else if((p->getX()[2]>(domainSize[2]-maxDistance))&&(p->getX()[2]<domainSize[2])){
				applyForce(p, 2, false);
			}
			p = actCell->getNextItem();
		}
	}*/
}

void ReflectingBoundary::applyForce(Particle* p, int axis, bool orientation){
	Particle* counterP = new Particle(*p);
	if(orientation){
		counterP->getX()[axis] = 0;
	}else{
		counterP->getX()[axis] = domainSize[axis];
	}
	//Particle** pa = new Particle*[2];
	//pa[0] = p;
	//pa[1] = counterP;
	std::vector<Particle*> pa;
	pa.push_back(p);
	pa.push_back(counterP);
	ParticleContainer pc(2);
	pc.setParticles(pa);
	calculation->setParticleContainer(pc);
	calculation->calculateForce();
	delete counterP;
	delete &pc;
}
