/*
 * Calculation.cpp
 * This class represents a strategy pattern. The three basic calculation functions are mapped to their actual algorithm.
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include "Calculation.h"
using namespace std;

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
	Particle *p1,*p2;
	double sigma_tmp;
	double epsilon_tmp;
	while((p1 = particleContainer.nextParticlePair1()) != NULL) {
		while((p2 = particleContainer.nextParticlePair2()) != NULL) {
			if(p->getType()!=curP->getType()){
				epsilon_tmp = sqrt(p->getEpsilon()*curP->getEpsilon());
				sigma_tmp = (p->getSigma()+curP->getSigma())/2.0;
			}else{
				epsilon_tmp = p->getEpsilon();
				sigma_tmp = p->getSigma();
			}
			double dist = ((p1->getX() -(p2->getX())).L2Norm());
			double factor1 = (24 * epsilon_tmp)/pow(dist,2);
			double factor2 = pow((sigma_tmp/dist),6)- (2*pow((sigma_tmp/dist),12));
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
	ParticleContainer** pcArray = lcDomain.getCells();
	int size = lcDomain.getNumberOfCells();
	ParticleContainer* pc;
	Particle* curP;
	double sigma_tmp;
	double epsilon_tmp;
	 
	std::vector<ParticleContainer*> neighboursOfPc;
	for(int i = 0; i < size; i++){
		pc = pcArray[i];
		
		lcDomain.getNeighbourCells(pc, &neighboursOfPc);
		neighboursOfPc.push_back(pc);
		int sizeNeighbours = neighboursOfPc.size();
		Particle* p;
		int cellParticleIt = 0;
		while((p = pc->nextParticle(&cellParticleIt))!=NULL){
			for(int j = 0; j < sizeNeighbours;j++){
				int interactingParticlesIt = 0;
				while((curP = neighboursOfPc[j]->nextParticle(&interactingParticlesIt))!=NULL){
					if((curP->getDistanceTo(p)<=lcDomain.getCutOffRadius())&&(curP->getDistanceTo(p)>0)){
						if(p->getType()!=curP->getType()){
							epsilon_tmp = sqrt(p->getEpsilon()*curP->getEpsilon());
							sigma_tmp = (p->getSigma()+curP->getSigma())/2.0;
						}else{
							epsilon_tmp = p->getEpsilon();
							sigma_tmp = p->getSigma();
						}

						double dist = ((p->getX() -(curP->getX())).L2Norm());
						double factor1 = (24 * epsilon_tmp)/pow(dist,2);
						double factor2 = pow((sigma_tmp/dist),6)- (2*pow((sigma_tmp/dist),12));
						utils::Vector<double,3> factor3 = curP->getX()-p->getX();
						utils::Vector<double,3> forceIJ = factor1 * factor2 * factor3;
						p->addOnF(forceIJ);
					}
				}
			}
			EnvInfl::getInstance()->calculateGravity(p);
		}
		neighboursOfPc.clear();
	}
}

void Sheet3Calc::calculateAll() {
	LOG4CXX_TRACE(loggerCalc, "starting new calculation loop of Sheet2Calc");
	calculateVelocity();
	calculatePosition();
	lcDomain.reset();
	calculateForce();
}

void Sheet3Calc::calculateSingleForce(Particle* p1, Particle* p2, double sigma_, double epsilon_){
	double dist = ((p1->getX() -(p2->getX())).L2Norm());
	double factor1 = (24 * p1->getEpsilon())/pow(dist,2);
	double factor2 = pow((p1->getSigma()/dist),6)- (2*pow((p1->getSigma()/dist),12));
	utils::Vector<double,3> factor3 = p2->getX()-p1->getX();
	utils::Vector<double,3> forceIJ = factor1 * factor2 * factor3;
	p1->addOnF(forceIJ);
}
