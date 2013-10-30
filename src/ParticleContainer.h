#include <list>
#include "Particle.h"
#include <sstream>
#include <iostream>

class ParticleContainer {
	private:
		double 
			start_time,
			end_time,
			delta_t;
		std::list<Particle> particles;

		std::list<Particle>::iterator nextP;
		std::list<Particle>::iterator nextPP1;
		std::list<Particle>::iterator nextPP2;

	public:
		ParticleContainer(std::list<Particle> particles, double start_time, double end_time, double delta_t);
		void calculate();
		void calculateX();
		void calculateF();
		void calculateV();
		void plotParticles(int iteration);
		bool getNextPair(Particle *p1, Particle *p2);
		bool getNextParticle(Particle *p);
		int innerpos;
};