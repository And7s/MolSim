/*
 * Calculation.cpp
 * This class represents a strategy pattern. The three basic calculation functions are mapped to their actual algorithm.
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include "Calculation.h"

void Calculation::setDeltaT(double delta_t) {
	this->delta_t = delta_t;
}

double Calculation::getDeltaT(){
	return delta_t;
}

void Calculation::resetForce() {
	Particle* p;

	while((p = particleContainer.nextParticle()) != NULL) {
		p->setOldF(p->getF());
		utils::Vector<double, 3> z = utils::Vector<double, 3> (0.);
		p->setF(z);
	}

}

void Sheet1Calc::setParticleContainer(ParticleContainer& pc_) {
	this->particleContainer = pc_;
}

ParticleContainer& Sheet1Calc::getParticleContainer(){
	return particleContainer;
}

void Sheet1Calc::calculateForce() {

	resetForce();
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

void Sheet1Calc::calculatePosition() {

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

void Sheet1Calc::calculateVelocity() {
	Particle* p;

	while((p = particleContainer.nextParticle()) != NULL) {
		utils::Vector<double, 3> old_v = p->getV();
		double scalar = getDeltaT()/(2*p->getM());
		utils::Vector<double, 3> new_acc = (p->getOldF()+(p->getF()))*(scalar);
		utils::Vector<double, 3> new_v = old_v +(new_acc);
		p->setV(new_v);
	}
}

void Sheet1Calc::calculateAll(){
	calculatePosition();
	calculateForce();
	calculateVelocity();
}