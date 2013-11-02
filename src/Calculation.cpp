/*
 * Calculation.cpp
 * This class represents a strategy pattern. The three basic calculation functions are mapped to their actual algorithm.
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include "Calculation.h"

ParticleContainer& Calculation::getParticleContainer(){
		return particleContainer;
}

void Calculation::setParticleContainer(ParticleContainer& particleContainer) {
		this->particleContainer = particleContainer;
}

void Calculation::setDeltaT(int delta_t) {
	this->delta_t = delta_t;
}

int Calculation::getDeltaT(){
	return delta_t;
}

void Sheet1Calc::calculateForce() {
	resetForce();
	getParticleContainer().resetIterator();
	while(!getParticleContainer().isFinished(0)){
		getParticleContainer().nextParticle(getParticleContainer().getActParticle());
		while(!getParticleContainer().isFinished(1)){
			if(getParticleContainer().getInnerParticle()!=getParticleContainer().getActParticle()){
				Particle& p1 = *getParticleContainer().getActParticle();
				Particle& p2 = *getParticleContainer().getInnerParticle();
				// insert calculation of force here!
				double euclidian_norm = ((p1.getX() -(p2.getX())).L2Norm());
				double pow_3 = std::pow(euclidian_norm,3);
				double mass_squared = (p1.getM()*p2.getM());
				double scalar = mass_squared/pow_3;

				utils::Vector<double, 3> forceIJ = (p2.getX()-(p1.getX()))*(scalar);
				p1.addOnF(forceIJ);
				p2.addOnF(forceIJ*(-1));
			}
			getParticleContainer().nextParticle(getParticleContainer().getInnerParticle());
		}
		getParticleContainer().nextParticle(getParticleContainer().getActParticle());
	}
}

void Sheet1Calc::calculatePosition() {

	getParticleContainer().resetIterator();

	while(!getParticleContainer().isFinished(0)){
		Particle& p = *getParticleContainer().getActParticle();
		utils::Vector<double, 3> old_pos = p.getX();
		utils::Vector<double, 3> new_v = p.getV()*(getDeltaT());
		double scalar = getDeltaT()*getDeltaT()/(2*p.getM());
		utils::Vector<double, 3> new_force = p.getF() * (scalar);
		utils::Vector<double, 3> newX = old_pos +(new_v+(new_force));
		p.setX(newX);
		getParticleContainer().nextParticle(getParticleContainer().getActParticle());
	}

}

void Sheet1Calc::calculateVelocity() {
	getParticleContainer().resetIterator();

	while(!getParticleContainer().isFinished(0)){
		// insert calculation of velocity here!
		Particle& p = *getParticleContainer().getActParticle();
		utils::Vector<double, 3> old_v = p.getV();
		double scalar = getDeltaT()/(2*p.getM());
		utils::Vector<double, 3> new_acc = (p.getOldF()+(p.getF()))*(scalar);
		utils::Vector<double, 3> newV = old_v +(new_acc);
		p.setV(newV);
		getParticleContainer().nextParticle(getParticleContainer().getActParticle());
	}
}

void Sheet1Calc::resetForce() {
	getParticleContainer().resetIterator();

	while(!getParticleContainer().isFinished(0)){
		Particle& p = *getParticleContainer().getActParticle();
		p.setOldF(p.getF());
		p.setF(utils::Vector<double, 3> (0.));
	}
}
