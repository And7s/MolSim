#include <list>
#include "Particle.h"
#include <functional>
#include <sstream>
#include <iostream>

class ParticleContainer {
	public:
		void perParticle(std::function<void (Particle&)> fn);
		void pairOfParticles(std::function<void (Particle&, Particle&)> fn);
		std::list<Particle> getParticles();
};
