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

/**
 * This class handles particles, whose force calculation differs from the normal behaviour.
 * e.g. the fixed particles in a membran.
 */
class SpecializedParticle {
private:
	/**
	 * a reference to the actual particle, whose force has to be manipulated.
	 */
	Particle* part;

	double startTime;
	double endTime;

	/**
	 * quite ugly to use a utils vector.. maybe we should change the Particle-implementation some day...
	 */
	utils::Vector<double,3> constForce;

	/**
	 * @see setConstForce()
	 */
	bool relative;

public:
	SpecializedParticle(Particle* part);
	virtual ~SpecializedParticle();

	inline Particle* getParticle();
	inline double getStartTime();
	inline double getEndTime();


	/**
	 * force will be manipulated after this timestamp. (in seconds)
	 */
	void setStartTime(double sT);
	/**
	 * upon this time, force will be manipulated (in seconds)
	 */
	void setEndTime(double eT);

	/**
	 * the force, which will be applied in each timestep.
	 * @param relative If relative is set to true, the force will be added to the previously calculated force. Otherwise, this calculated force will be replaced.
	 */
	void setConstForce(std::vector<double> force, bool relative);

	/**
	 * the actual calculating method.
	 */
	void adjustForce(int timestep);
};

Particle* SpecializedParticle::getParticle(){	//inline
	return this->part;
}

double SpecializedParticle::getStartTime(){		//inline
	return this->startTime;
}

double SpecializedParticle::getEndTime(){		//inline
	return this->endTime;
}

#endif /* SPECIALIZEDPARTICLE_H_ */
