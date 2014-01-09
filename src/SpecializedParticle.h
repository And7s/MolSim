/*
 * SpecializedParticle.h
 *
 *  Created on: Jan 9, 2014
 *      Author: paul
 */

#ifndef SPECIALIZEDPARTICLE_H_
#define SPECIALIZEDPARTICLE_H_

#include "Particle.h"
#include <vector>
#include "utils/Vector.h"

using namespace std;

class SpecializedParticle {
private:
	Particle* part;

	double startTime;
	double endTime;

	/**
	 * quite ugly to use a utils vector.. maybe we should change the Particle-implementation some day...
	 */
	utils::Vector<double,3> constForce;

	bool relative;

public:
	SpecializedParticle(Particle* part);
	virtual ~SpecializedParticle();

	inline Particle* getParticle();
	inline double getStartTime();
	inline double getEndTime();


	void setStartTime(double sT);
	void setEndTime(double eT);

	/**
	 * the force, which will be applied in each timestep.
	 * If relative is set to true, the force will be added to the previously calculated force. Otherwise, this calculated force will be replaced.
	 */
	void setConstForce(std::vector<double> force, bool relative);

	/**
	 * the actual calculating method.
	 */
	void adjustForce(int timestep);
};

Particle* SpecializedParticle::getParticle(){
	return this->part;
}

double SpecializedParticle::getStartTime(){
	return this->startTime;
}

double SpecializedParticle::getEndTime(){
	return this->endTime;
}

#endif /* SPECIALIZEDPARTICLE_H_ */
