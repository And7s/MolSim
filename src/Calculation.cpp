/*
 * Calculation.cpp
 * This class represents a strategy pattern. The three basic calculation functions are mapped to their actual algorithm.
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include "Calculation.h"

/**
 * Logger
 */
LoggerPtr loggerCalc(Logger::getLogger( "main.calc"));

void Calculation::setDeltaT(double delta_t) {
	this->delta_t = delta_t;
}

LCDomain& Calculation::getLcDomain(){
	return lcDomain;
}

void Calculation::setLcDomain(LCDomain& lcDomain) {
	this->lcDomain = lcDomain;
}

double Calculation::getDeltaT(){
	return delta_t;
}

void Calculation::calculateAll(){
	calculatePosition();
	calculateForce();
	calculateVelocity();
}

void Calculation::calculatePosition(){

	ParticleContainer** pcArray = lcDomain.getCells();
	int size = lcDomain.getNumberOfCells();

	for(int i = 0; i<size;i++){
		Particle* p;
		while((p = pcArray[i]->nextParticle())!=NULL){
			utils::Vector<double, 3> old_pos = p->getX();
			utils::Vector<double, 3> new_v = p->getV()*(getDeltaT());
			double scalar = getDeltaT()*getDeltaT()/(2*p->getM());
			utils::Vector<double, 3> new_force = p->getF() * (scalar);
			utils::Vector<double, 3> newX = old_pos +(new_v+(new_force));
			p->setX(newX);
		}
	}
	std::cout << "Position: " << std::endl;
	/*
	Particle* p;
	//LOG4CXX_INFO(loggerCalc, "In CalculatePosition");
	while((p = particleContainer.nextParticle()) != NULL) {
		utils::Vector<double, 3> old_pos = p->getX();
		utils::Vector<double, 3> new_v = p->getV()*(getDeltaT());
		double scalar = getDeltaT()*getDeltaT()/(2*p->getM());
		utils::Vector<double, 3> new_force = p->getF() * (scalar);
		utils::Vector<double, 3> newX = old_pos +(new_v+(new_force));
		p->setX(newX);
	}*/
}

void Calculation::calculateVelocity(){
	ParticleContainer** pcArray = lcDomain.getCells();
	int size = lcDomain.getNumberOfCells();

	for(int i = 0; i<size;i++){
		Particle* p;
		while((p = pcArray[i]->nextParticle())!=NULL){
			utils::Vector<double, 3> old_v = p->getV();
			double scalar = getDeltaT()/(2*p->getM());
			utils::Vector<double, 3> new_acc = (p->getOldF()+(p->getF()))*(scalar);
			utils::Vector<double, 3> new_v = old_v +(new_acc);
			p->setV(new_v);
		}
	}
	/*
	Particle* p;
	//LOG4CXX_INFO(loggerCalc, "In CalculateVelocity");
	while((p = particleContainer.nextParticle()) != NULL) {
		utils::Vector<double, 3> old_v = p->getV();
		double scalar = getDeltaT()/(2*p->getM());
		utils::Vector<double, 3> new_acc = (p->getOldF()+(p->getF()))*(scalar);
		utils::Vector<double, 3> new_v = old_v +(new_acc);
		p->setV(new_v);
	}*/
}

void Calculation::resetForce() {
	ParticleContainer** pcArray = lcDomain.getCells();
	int size = lcDomain.getNumberOfCells();

	for(int i = 0; i<size;i++){
		Particle* p;
		while((p = pcArray[i]->nextParticle())!=NULL){
			p->setOldF(p->getF());
			utils::Vector<double, 3> z = utils::Vector<double, 3> (0.);
			p->setF(z);
		}
	}
	/*
	Particle* p;
	while((p = particleContainer.nextParticle()) != NULL) {
		p->setOldF(p->getF());
		utils::Vector<double, 3> z = utils::Vector<double, 3> (0.);
		p->setF(z);
	}
	*/
}

void Calculation::setParticleContainer(ParticleContainer& pc_) {
	this->particleContainer = pc_;
}

ParticleContainer& Calculation::getParticleContainer(){
	return particleContainer;
}

void Sheet1Calc::calculateForce() {
	Particle* p1,* p2;
	while((p1 = particleContainer.nextParticlePair1()) != NULL) {
		while((p2 = particleContainer.nextParticlePair2()) != NULL) {
			double euclidian_norm = ((p1->getX() -(p2->getX())).L2Norm());
			double pow_3 = std::pow(euclidian_norm,3);
			double mass_squared = (p1->getM()*p2->getM());
			double scalar = mass_squared/pow_3;
			utils::Vector<double, 3> forceIJ = (p2->getX()-(p1->getX()))*(scalar);
			p1->addOnF(forceIJ);
			utils::Vector<double, 3> forceJI = forceIJ *(-1);
			p2->addOnF(forceJI);
		}
	}
}

void Sheet1Calc::calculateAll(){
	LOG4CXX_TRACE(loggerCalc, "starting new calculation loop of Sheet1Calc");
	calculateVelocity();
	calculatePosition();
	calculateForce();
}

void Sheet2Calc::calculateForce() {
	double epsilon = 5.0;
	double sigma = 1.0;
	Particle *p1,*p2;
	while((p1 = particleContainer.nextParticlePair1()) != NULL) {
		while((p2 = particleContainer.nextParticlePair2()) != NULL) {
			double dist = ((p1->getX() -(p2->getX())).L2Norm());
			double factor1 = (24 * epsilon)/pow(dist,2);
			double factor2 = pow((sigma/dist),6)- (2*pow((sigma/dist),12));
			utils::Vector<double,3> factor3 = p2->getX()-p1->getX();
			utils::Vector<double,3> forceIJ = factor1 * factor2 * factor3;
			utils::Vector<double,3> forceJI = (-1) * forceIJ;
			p1->addOnF(forceIJ);
			p2->addOnF(forceJI);
		}
	}
}

void Sheet2Calc::calculateAll() {
	LOG4CXX_TRACE(loggerCalc, "starting new calculation loop of Sheet2Calc");
	calculateVelocity();
	calculatePosition();
	calculateForce();
}

void Sheet3Calc::calculateForce() {
	double epsilon = 5.0;
	double sigma = 1.0;

	ParticleContainer** pcArray = lcDomain.getCells();
	int size = lcDomain.getNumberOfCells();
	ParticleContainer* pc;
	for(int i = 0; i < size; i++){
		pc = pcArray[i];
		std::vector<ParticleContainer*> neighboursOfPc;
		lcDomain.getNeighbourCells(pc, &neighboursOfPc);
		neighboursOfPc.push_back(pc);
		int sizeNeighbours = neighboursOfPc.size();
		Particle* p;
		while((p = pc->nextParticle())!=NULL){
			for(int j = 0; j < sizeNeighbours;j++){
				Particle* curP;
				while((curP = neighboursOfPc[j]->nextParticle())!=NULL){
					if((curP->getDistanceTo(p)<=lcDomain.getCutOffRadius())&&(curP->getDistanceTo(p)>0)){
						double dist = ((p->getX() -(curP->getX())).L2Norm());
						double factor1 = (24 * epsilon)/pow(dist,2);
						double factor2 = pow((sigma/dist),6)- (2*pow((sigma/dist),12));
						utils::Vector<double,3> factor3 = curP->getX()-p->getX();
						utils::Vector<double,3> forceIJ = factor1 * factor2 * factor3;
						p->addOnF(forceIJ);
					}
				}
			}
		}
	}
}

void Sheet3Calc::calculateAll() {
	LOG4CXX_TRACE(loggerCalc, "starting new calculation loop of Sheet2Calc");
	calculateVelocity();
	calculatePosition();
	lcDomain.reset();
	calculateForce();

}
