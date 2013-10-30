/*
This class represents a strategy pattern. The three basic calculation functions are mapped to their actual algorithm.

*/



#include <iostream>
#include "ParticleCollection.h"
#include "Calculation.h"


using namespace std;


		void Calculation::calculateForce(){};

		void Calculation::calculatePosition(){};

		void Calculation::calculateVelocity(){};



		void Calculation::setParticleCollection(ParticleCollection * p) {
			pc = p;
		}

		void Calculation::setDeltaT(int deltaT){
			delta_t = deltaT;
		}



		void Sheet1Calc::calculateForce(){
	
			//reset
			Particle pp;
			while(pc->getNextParticle(pp)){
				Particle* p1 = (&pp);
				p1->setOldF(p1->getF());
				p1->setF(p1->getF()*0);
			}
			//get particle pair, by passing pointers
			Particle pp1;
			Particle pp2;
			while(pc->getNextParticlePair(pp1,pp2)){
				Particle* p1 = (&pp1);
				Particle* p2 = (&pp2);
				double tmp = ((p1->getX().operator -(p2->getX())).L2Norm());
				double tmp2 = std::pow(tmp,3);
				double tmp3 = (p1->getM()*p2->getM());
				double scalar = tmp3/tmp2;
				utils::Vector<double, 3> forceIJ = (p2->getX().operator-(p1->getX())).operator*(scalar);
				p1->addOnF(forceIJ);
				p2->addOnF(forceIJ*(-1));
			}
		}

		void Sheet1Calc::calculatePosition(){
			Particle pp;
			pc->getNextParticle(pp);
			Particle* p = (&pp);
			utils::Vector<double, 3> part1 = p->getX();
			utils::Vector<double, 3> part2 = p->getV()*(delta_t);
			double scalar = delta_t*delta_t/(2*p->getM());
			utils::Vector<double, 3> part3 = p->getF() * (scalar);
			utils::Vector<double, 3> newX = part1 +(part2 +(part3));
			p->setX(newX);
		}

		void Sheet1Calc::calculateVelocity(){
			Particle pp;
			pc->getNextParticle(pp);
			Particle* p = (&pp);
			utils::Vector<double, 3> part1 = p->getV();
			double scalar = delta_t/(2*p->getM());
			utils::Vector<double, 3> part2 = (p->getOldF().operator+(p->getF())).operator *(scalar);
			utils::Vector<double, 3> newV = part1 +(part2);
			p->setV(newV);
		}
