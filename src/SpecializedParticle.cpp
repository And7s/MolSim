/*
 * SpecializedParticle.cpp
 *
 *  Created on: Jan 9, 2014
 *      Author: paul
 */

#include "SpecializedParticle.h"


SpecializedParticle::SpecializedParticle(Particle* part) {
	this->part = part;
}

SpecializedParticle::~SpecializedParticle() {
	// TODO Auto-generated destructor stub
}

void SpecializedParticle::setStartTime(double sT) {
	startTime = sT;
}

void SpecializedParticle::setEndTime(double eT) {
	endTime = eT;
}

void SpecializedParticle::setConstForce(std::vector<double> force,
		bool relative) {
	double f[] = {force[0],force[1],force[2]};
	this->constForce = f;
	this->relative = relative;
}

void SpecializedParticle::adjustForce(int timestep){
	if(timestep >= startTime && timestep < endTime){
		if(relative){
			this->part->addOnF(constForce);
		}else{
			this->part->setF(constForce);
		}
	}
}
