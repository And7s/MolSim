#include "ParticleContainer.h"

class Calculation : public ParticleContainer {

private:
	ParticleContainer particleContainer;
	int delta_t;

public:

	virtual ~Calculation(){}

	virtual void calculateForce()=0;
	
	virtual void calculatePosition()=0;

	virtual void calculateVelocity()=0;

	void resetForce();

	void setDeltaT(int deltaT);

	int getDeltaT();

	ParticleContainer& getParticleContainer();

	void setParticleContainer(ParticleContainer& particleContainer);
};

class Sheet1Calc : public Calculation{

public:

	void calculateForce();
	
	void calculatePosition();

	void calculateVelocity();

	void resetForce();

	void setDeltaT(int deltaT);

	int getDeltaT();

	ParticleContainer& getParticleContainer();

	void setParticleContainer(ParticleContainer& particleContainer);
};

