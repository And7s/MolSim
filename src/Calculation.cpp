/*
This class represents a strategy pattern. The three basic calculation functions are mapped to their actual algorithm.

*/

//#include "Calculation.h"
#include "ParticleContainer.h"

#include <iostream>
#include <unistd.h>

using namespace std;

extern std::list<Particle> particles;

class Calculation
{

	public:
		virtual void calculateForce() = 0;

		virtual void calculatePosition() = 0;

		virtual void calculateVelocity() = 0;

		ParticleContainer * pc;
		
		//std::list<Particle> particle;
		
		int delta_t;

		//void setParticles(std::list<Particle>& part){
		//		particle = part;
		//}

		void setParticleContainer(ParticleContainer * p) {
			pc = p;
		}
		
		ParticleContainer* getParticleContainter() {
			return pc;
		}

		void setDeltaT(int deltaT){
			delta_t = deltaT;
		}

		void calcAll(){
			calculatePosition();
			calculateForce();
			calculateVelocity();
		}
};

class Sheet1Calc : public Calculation
{
	public:
		
		
		void calculateForce(){
			
			list<Particle>::iterator iterator;
			iterator = particles.begin();

			for (iterator = particles.begin(); iterator != particles.end();++iterator){
					Particle& p = *iterator;
					p.setOldF(p.getF());
					p.setF(utils::Vector<double, 3> (0.0));
			}

			iterator = particles.begin();

			while (iterator != particles.end()) {
				list<Particle>::iterator innerIterator = iterator;
				++innerIterator;

				while (innerIterator != particles.end()) {
					if (innerIterator != iterator) {

						Particle& p1 = *iterator;
						Particle& p2 = *innerIterator;
						// insert calculation of force here!
						double tmp = ((p1.getX().operator -(p2.getX())).L2Norm());
						double tmp2 = std::pow(tmp,3);
						double tmp3 = (p1.getM()*p2.getM());
						double scalar = tmp3/tmp2;

						utils::Vector<double, 3> forceIJ = (p2.getX().operator-(p1.getX())).operator*(scalar);
						p1.addOnF(forceIJ);
						p2.addOnF(forceIJ*(-1));
					}
					++innerIterator;
				}
				++iterator;
			}
		}

		void calculatePosition(){
			list<Particle>::iterator iterator = particles.begin();
			while (iterator != particles.end()) {
				Particle& p = *iterator;
				utils::Vector<double, 3> part1 = p.getX();
				utils::Vector<double, 3> part2 = p.getV().operator*(delta_t);
				double scalar = delta_t*delta_t/(2*p.getM());
				utils::Vector<double, 3> part3 = p.getF() * (scalar);
				utils::Vector<double, 3> newX = part1.operator +(part2.operator +(part3));
				p.setX(newX);

				++iterator;
			}
		}

		void calculateVelocity(){
			list<Particle>::iterator iterator = particles.begin(); 
			while (iterator != particles.end()) {

				Particle& p = *iterator;
				// insert calculation of velocity here!
				utils::Vector<double, 3> part1 = p.getV();
				double scalar = delta_t/(2*p.getM());
				utils::Vector<double, 3> part2 = (p.getOldF().operator+(p.getF())).operator *(scalar);
				utils::Vector<double, 3> newV = part1.operator +(part2);
				p.setV(newV);

				++iterator;
			}
		}
};
