#ifndef CALCULATION_H_
#define CALCULATION_H_

class Calculation {

public:
	virtual void calculateForce();
	
	virtual void calculatePosition();

	virtual void calculateVelocity();

	void setParticleCollection(ParticleCollection * p);

	void setDeltaT(int deltaT);
	
	ParticleCollection * pc;
	
	int delta_t;


};

class Sheet1Calc : public Calculation{

public:
	void calculateForce();
	
	void calculatePosition();

	void calculateVelocity();
};
#endif