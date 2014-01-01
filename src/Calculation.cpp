/*
 * Calculation.cpp
 * This class represents a strategy pattern. The three basic calculation functions are mapped to their actual algorithm.
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#include "Calculation.h"
using namespace std;

/**
 * Logger
 */
LoggerPtr loggerCalc(Logger::getLogger( "main.calc"));

void Calculation::setDeltaT(double delta_t) {
	this->delta_t = delta_t;
}

LCDomain* Calculation::getLcDomain(){
	return lcDomain;
}

void Calculation::setLcDomain(LCDomain* lcDomain_) {
	lcDomain = lcDomain_;
}

double Calculation::getDeltaT(){
	return delta_t;
}



void Calculation::calculatePosition(){

	Particle* p;
	std::vector<Particle*>* parts = lcDomain->getAllParticles();
	#pragma omp parallel for private(p)
	for(int i = 0; i < parts->size() ;i++){
		p = (*parts)[i];
		if(p->getType() != -1) {
			utils::Vector<double, 3> old_pos = p->getX();
			utils::Vector<double, 3> new_v = p->getV()*(delta_t);
			double scalar = delta_t*delta_t/(2*p->getM());
			utils::Vector<double, 3> new_force = p->getF() * (scalar);
			utils::Vector<double, 3> newX = old_pos +(new_v+(new_force));
			p->setX(newX);
		}
	}
}

void Calculation::calculateVelocity(){

	std::vector<Particle*>* parts = lcDomain->getAllParticles();
	Particle* p;
	#pragma omp parallel for private(p)
	for(int i = 0; i < parts->size(); i++){
		p = (*parts)[i];
		utils::Vector<double, 3> old_v = p->getV();
		double scalar = delta_t/(2*p->getM());
		utils::Vector<double, 3> new_acc = (p->getOldF()+(p->getF()))*(scalar);
		utils::Vector<double, 3> new_v = old_v +((p->getOldF()+(p->getF()))*(scalar));
		p->setV(new_v);
	}
}

void Calculation::resetForce() {
	Particle* p;
	std::vector<Particle*>* particles = lcDomain->getAllParticles();
	#pragma omp parallel for private(p)
	for(int i = 0;i < particles->size();i++){
		(*particles)[i]->resetForce();
	}
}

void Calculation::setParticleContainer(ParticleContainer& pc_) {
	this->particleContainer = pc_;
}

ParticleContainer& Calculation::getParticleContainer(){
	return particleContainer;
}

void Sheet3Calc::calculateForce() {
//sheet 5 calculation
	ParticleContainer** pcArray = lcDomain->getCells();
	int 
		size = lcDomain->getNumberOfCells(),
		interactingParticlesIt,
		cellParticleIt,
		sizeNeighbours;
	ParticleContainer* pc;
	Particle
		*curP,
		*p;
	double 
		sigma_tmp,
		epsilon_tmp,
		cutoff = lcDomain->getCutOffRadius(),
		cutoffSq = lcDomain->getCutOffRadius()*lcDomain->getCutOffRadius(),
		factor1,
		factor2,
		powSigma,
		powDist;
	std::vector<ParticleContainer*> neighboursOfPc;
	utils::Vector<double,3> 
		factor3,
		forceIJ;

	
	//Variables for Membrane simulation

	double k = 300;//make me dynmaic TODO
	double r0 = 2.2;	//distance, take from input file pls
	double r0sqrt = std::sqrt(2)*r0;
	double mindist = std::pow(2, 1/6);
	int sidelength = 50;	//This needs to be calculated/set by the input of the membran

	//#pragma omp parallel for private(pc, sigma_tmp, epsilon_tmp,factor1, forceIJ, factor2, powSigma, powDist, factor3, neighboursOfPc, curP, p, interactingParticlesIt, cellParticleIt, sizeNeighbours) 
	#pragma omp parallel for schedule(dynamic) private(pc, sigma_tmp, epsilon_tmp,factor1, forceIJ, factor2, powSigma, powDist, factor3, neighboursOfPc, curP, p, interactingParticlesIt, cellParticleIt, sizeNeighbours) 
	for(int i = 0; i < size; i++){	//iterate over all cells

		pc = pcArray[i];

		lcDomain->getNeighbourCells(pc, &neighboursOfPc);
		neighboursOfPc.push_back(pc);
		sizeNeighbours = neighboursOfPc.size();
		
		cellParticleIt = 0;
		
		while((p = pc->nextParticle(&cellParticleIt))!=NULL){	//iterate over particles within this cell
			
			if(p->getType() != -1) {
				for(int j = 0; j < sizeNeighbours;j++){		//iterate over their neighbours
					interactingParticlesIt = 0;
					while((curP = neighboursOfPc[j]->nextParticle(&interactingParticlesIt))!=NULL){


						int typa = p->getUid();
						int typb = curP->getUid();

					
						if(typa != typb) {
							factor3 = curP->getX() - p->getX();
							double length = factor3.L2Norm();

						
							int x = typa % sidelength;
							int y = typa / sidelength;

							int xb = typb % sidelength;
							int yb = typb / sidelength;

							if(	//Direct neighbour
								(std::abs(y-yb) <= 1 && x == xb) ||
								(std::abs(x-xb) <= 1 && y == yb)) {
									forceIJ = (length-r0)*k*factor3/length;
									p->addOnF(forceIJ);
							}else if (std::abs(x-xb) <= 1 && std::abs(y-yb) <= 1 ) {		//diagonal neighbour
								forceIJ = (length-r0sqrt)*k*factor3/length;
								p->addOnF(forceIJ);
							} else {
								if(length >= mindist && length <= cutoff){ 
									double distSq = length*length;
									if(p->getType()!=curP->getType()){
										epsilon_tmp = sqrt(p->getEpsilon()*curP->getEpsilon());
										sigma_tmp = (p->getSigma()+curP->getSigma())/2.0;
									}else{
										epsilon_tmp = p->getEpsilon();
										sigma_tmp = p->getSigma();
									}

									factor1 = (24 * epsilon_tmp)/distSq;
									powSigma = pow(sigma_tmp,6);
									powDist = pow(distSq,3);
									factor2 = powSigma/powDist- (2*pow(powSigma, 2)/pow(powDist,2));
									
									forceIJ = factor1 * factor2 * factor3*(-1);
									p->addOnF(forceIJ);
								}
							}
						}		
					}
				}
				EnvInfl::getInstance()->calculateGravity(p);
			}
		}
		neighboursOfPc.clear();
	}

}



void Sheet3Calc::calculateAll() {
	LOG4CXX_TRACE(loggerCalc, "starting new calculation loop of Sheet3Calc");
	calculateForce();
	calculateVelocity();
	calculatePosition();
	lcDomain->reset();
}

void Sheet3Calc::calculateSingleForce(Particle* p1, Particle* p2){
	double dist = ((p1->getX() -(p2->getX())).L2Norm());
	double factor1 = (24 * p1->getEpsilon())/pow(dist,2);
	double factor2 = pow((p1->getSigma()/dist),6)- (2*pow((p1->getSigma()/dist),12));
	utils::Vector<double,3> factor3 = p2->getX()-p1->getX();
	utils::Vector<double,3> forceIJ = factor1 * factor2 * factor3;
	p1->addOnF(forceIJ);
}
