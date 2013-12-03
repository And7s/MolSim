/*
 * Calculation2.cpp
 * This class represents a strategy pattern. The three basic calculation functions are mapped to their actual algorithm.
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include "Calculation2.h"

/**
 * Logger
 */
LoggerPtr loggerCalc2(Logger::getLogger( "main.calc2"));

void Calculation2::setDeltaT(double delta_t) {
	this->delta_t = delta_t;
}

double Calculation2::getDeltaT(){
	return delta_t;
}

void Calculation2::calculateAll(){
	calculatePosition();
	calculateForce();
	calculateVelocity();
}

void Calculation2::calculatePosition(){

	Particle* p;

	while((p = particleContainer.getNextParticle()) != NULL) {
		utils::Vector<double, 3> old_pos = p->getX();
		utils::Vector<double, 3> new_v = p->getV()*(getDeltaT());
		double scalar = getDeltaT()*getDeltaT()/(2*p->getM());
		utils::Vector<double, 3> new_force = p->getF() * (scalar);
		utils::Vector<double, 3> newX = old_pos +(new_v+(new_force));
		p->setX(newX);
	}
}

void Calculation2::calculateVelocity(){
	Particle* p;

	while((p = particleContainer.getNextParticle()) != NULL) {
		utils::Vector<double, 3> old_v = p->getV();
		double scalar = getDeltaT()/(2*p->getM());
		utils::Vector<double, 3> new_acc = (p->getOldF()+(p->getF()))*(scalar);
		utils::Vector<double, 3> new_v = old_v +(new_acc);
		p->setV(new_v);
	}
}

void Calculation2::resetForce() {
	Particle* p;

	while((p = particleContainer.getNextParticle()) != NULL) {
		p->setOldF(p->getF());
		utils::Vector<double, 3> z = utils::Vector<double, 3> (0.);
		p->setF(z);
	}

}

void Calculation2::setParticleContainer(ParticleContainer2& pc_) {
	this->particleContainer = pc_;
}

ParticleContainer2& Calculation2::getParticleContainer(){
	return particleContainer;
}


void Sheet1Calc2::setParticleContainer(ParticleContainer2& pc_) {
	this->particleContainer = pc_;
}

ParticleContainer2& Sheet1Calc2::getParticleContainer(){
	return particleContainer;
}

void Sheet1Calc2::calculateForce() {
	//resetForce();
	Particle* p1,* p2;
	ParticleContainer2::ParticlePair p(particleContainer.getNextPair());
	p1 = &p.first;
	p2 = &p.second;

	while(!((p.first)==(p.second))) {
		double euclidian_norm = ((p1->getX() -(p2->getX())).L2Norm());
		double pow_3 = std::pow(euclidian_norm,3);
		double mass_squared = (p1->getM()*p2->getM());
		double scalar = mass_squared/pow_3;

		utils::Vector<double, 3> forceIJ = (p2->getX()-(p1->getX()))*(scalar);
		p1->addOnF(forceIJ);
		utils::Vector<double, 3> forceJI = forceIJ *(-1);
		p2->addOnF(forceJI);
		ParticleContainer2::ParticlePair p(particleContainer.getNextPair());
		p1 = &p.first;
		p2 = &p.second;
	}
	delete &p;
}
/*
void Sheet1Calc2::calculatePosition() {

	Particle* p;

	while((p = particleContainer.nextParticle()) != NULL) {
		utils::Vector<double, 3> old_pos = p->getX();
		utils::Vector<double, 3> new_v = p->getV()*(getDeltaT());
		double scalar = getDeltaT()*getDeltaT()/(2*p->getM());
		utils::Vector<double, 3> new_force = p->getF() * (scalar);
		utils::Vector<double, 3> newX = old_pos +(new_v+(new_force));
		p->setX(newX);
	}
}

void Sheet1Calc2::calculateVelocity() {
	Particle* p;

	while((p = particleContainer.nextParticle()) != NULL) {
		utils::Vector<double, 3> old_v = p->getV();
		double scalar = getDeltaT()/(2*p->getM());
		utils::Vector<double, 3> new_acc = (p->getOldF()+(p->getF()))*(scalar);
		utils::Vector<double, 3> new_v = old_v +(new_acc);
		p->setV(new_v);
	}
}

void Sheet1Calc2::calculateAll(){
	LOG4CXX_TRACE(loggerCalc, "starting new calculation loop of Sheet1Calc2");
	calculatePosition();
	calculateForce();
	calculateVelocity();
}
*/
void Sheet2Calc2::calculateForce() {
	double epsilon = 5.0;
	double sigma = 1.0;
	Particle *p1,*p2;
	ParticleContainer2::ParticlePair p(particleContainer.getNextPair());
	p1 = &p.first;
	p2 = &p.second;
	//resetForce();
	while(!((p.first)==(p.second))) {
		double dist = ((p1->getX() -(p2->getX())).L2Norm());
		double factor1 = (24 * epsilon)/pow(dist,2);
		double factor2 = pow((sigma/dist),6)- (2*pow((sigma/dist),12));
		utils::Vector<double,3> factor3 = p2->getX()-p1->getX();
		utils::Vector<double,3> forceIJ = factor1 * factor2 * factor3;
		utils::Vector<double,3> forceJI = (-1) * forceIJ;
		p1->addOnF(forceIJ);
		p2->addOnF(forceJI);
		ParticleContainer2::ParticlePair p(particleContainer.getNextPair());
		p1 = &p.first;
		p2 = &p.second;
	}
	delete &p;
}
/*
void Sheet2Calc2::calculatePosition() {
	Particle* p;

	while((p = particleContainer.nextParticle()) != NULL) {
		utils::Vector<double, 3> old_pos = p->getX();
		utils::Vector<double, 3> new_v = p->getV()*(getDeltaT());
		double scalar = getDeltaT()*getDeltaT()/(2*p->getM());
		utils::Vector<double, 3> new_force = p->getF() * (scalar);
		utils::Vector<double, 3> newX = old_pos +(new_v+(new_force));
		p->setX(newX);
	}
}

void Sheet2Calc2::calculateVelocity() {
	Particle* p;

	while((p = particleContainer.nextParticle()) != NULL) {
		utils::Vector<double, 3> old_v = p->getV();
		double scalar = getDeltaT()/(2*p->getM());
		utils::Vector<double, 3> new_acc = (p->getOldF()+(p->getF()))*(scalar);
		utils::Vector<double, 3> new_v = old_v +(new_acc);
		p->setV(new_v);
	}
}

void Sheet2Calc2::calculateAll() {
	LOG4CXX_TRACE(loggerCalc, "starting new calculation loop of Sheet2Calc2");
	calculatePosition();
	calculateForce();
	calculateVelocity();
}
*/
void Sheet2Calc2::setParticleContainer(ParticleContainer2& pc_) {
	this->particleContainer = pc_;
}

ParticleContainer2& Sheet2Calc2::getParticleContainer() {
	return particleContainer;
}
