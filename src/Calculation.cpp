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
	//#pragma omp parallel for private(p)
	for(int i = 0; i < parts->size() ;i++){
		p = (*parts)[i];
		if(p->getType() != -1) {
			utils::Vector<double, 3> old_pos = p->getX();
			utils::Vector<double, 3> new_v = p->getV()*(delta_t);
			double scalar = delta_t*delta_t/(2*p->getM());
			utils::Vector<double, 3> new_force = p->getF() * (scalar);
			utils::Vector<double, 3> lastmove = (new_v+(new_force));
			utils::Vector<double, 3> newX = old_pos +lastmove;
		   
			p->setLastMove ( lastmove);
			p->setX(newX);

			for(int j = 0; j < 3; j++) {
				if(std::abs(lastmove[j]) >= 1.023) {
					std::cout << lastmove[j]<<"\n";
					std::cout << "===travels too far\n"<<*p<<"\n";
					exit(0);
				}
			}
		}
	}
}

void Calculation::calculateVelocity(){

	std::vector<Particle*>* parts = lcDomain->getAllParticles();
	Particle* p;
	//#pragma omp parallel for private(p)
	for(int i = 0; i < parts->size(); i++){
		p = (*parts)[i];
		utils::Vector<double, 3> old_v = p->getV();
		double scalar = delta_t/(2*p->getM());
		utils::Vector<double, 3> new_acc = (p->getOldF()+(p->getF()))*(scalar);
		utils::Vector<double, 3> new_v = old_v +((p->getOldF()+(p->getF()))*(scalar));
		utils::Vector<double, 3> dv = ((p->getOldF()+(p->getF()))*(scalar));
		p->setDeltaV(dv);
		p->setV(new_v);
	}
}

void Calculation::resetForce() {
	Particle* p;
	std::vector<Particle*>* particles = lcDomain->getAllParticles();
	//#pragma omp parallel for private(p)
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

void RayCalc::calculateForce() {
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
		cutHalf = lcDomain->getCutOffRadius() / 2.0,
		distSq,
		cutoffSq = lcDomain->getCutOffRadius()*lcDomain->getCutOffRadius(),
		factor1,
		factor2,
		powSigma,
		powDist;
	std::vector<ParticleContainer*> neighboursOfPc;
	utils::Vector<double,3>
		factor3,
		forceIJ;
	//Try me
	//#pragma omp parallel for private                (pc, sigma_tmp, epsilon_tmp, distSq,factor1, forceIJ, factor2, powSigma, powDist, factor3, neighboursOfPc, curP, p, interactingParticlesIt, cellParticleIt, sizeNeighbours)
	#pragma omp parallel for schedule(dynamic) private(pc, sigma_tmp, epsilon_tmp,factor1, forceIJ, factor2, powSigma, powDist, factor3, neighboursOfPc, curP, p, interactingParticlesIt, cellParticleIt, sizeNeighbours, distSq)   
	for(int i = 0; i < size; i++){        //iterate over all cells
		pc = pcArray[i];

		lcDomain->getNeighbourCells(pc, &neighboursOfPc);
		neighboursOfPc.push_back(pc);
		sizeNeighbours = neighboursOfPc.size();
		
		cellParticleIt = 0;
		
		while((p = pc->nextParticle(&cellParticleIt))!=NULL){        //iterate over particles within this cell
			
			if(p->getType() != -1) {
				if(p->getUid() == 6) {
				   // std::cerr << "check 6 vs "<<sizeNeighbours<<"\n";
				}
				for(int j = 0; j < sizeNeighbours;j++){                //iterate over their neighbours
					interactingParticlesIt = 0;
					while((curP = neighboursOfPc[j]->nextParticle(&interactingParticlesIt))!=NULL){

						/*
						 * Currently, the cutoff-rad is equal to the length of an cell.
						 * The likelihood, that two particles, which are located in neighbour-cells,
						 * have a higher distance than the cutoff-rad, is - depending on the the simulation - approximately 60%.
						 * The approxDist-inline-function checks, whether the particles is in the box, which embraces the circle.
						 * In the end, the actual distance has to be measured in only 3% of the cases.
						 * Reducing the length would reduce the amount of misses even more.
						 */
						if(p->approxDist(curP,cutHalf)){ //improves speed by about 4% + inline 1%
							distSq = curP->getDistanceToSq(p);
							if((distSq<=cutoffSq)&&(distSq>0)){
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
								factor3 = curP->getX()-p->getX();

								forceIJ = factor1 * factor2 * factor3;

								p->addOnF(forceIJ);
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

void MemCalc::calculateForce() {


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

	double k = 300;     //make me dynmaic TODO
	double r0 = 2.2;    //distance, take from input file pls
	double r0sqrt = std::sqrt(2)*r0;
	double mindist = std::pow(2, 1/6);
	int sidelength = 50;    //This needs to be calculated/set by the input of the membran

	//#pragma omp parallel for private(pc, sigma_tmp, epsilon_tmp,factor1, forceIJ, factor2, powSigma, powDist, factor3, neighboursOfPc, curP, p, interactingParticlesIt, cellParticleIt, sizeNeighbours) 
	#pragma omp parallel for schedule(dynamic) private(pc, sigma_tmp, epsilon_tmp,factor1, forceIJ, factor2, powSigma, powDist, factor3, neighboursOfPc, curP, p, interactingParticlesIt, cellParticleIt, sizeNeighbours) 
	for(int i = 0; i < size; i++){  //iterate over all cells

		pc = pcArray[i];

		lcDomain->getNeighbourCells(pc, &neighboursOfPc);
		neighboursOfPc.push_back(pc);
		sizeNeighbours = neighboursOfPc.size();
		
		cellParticleIt = 0;
		
		while((p = pc->nextParticle(&cellParticleIt))!=NULL){   //iterate over particles within this cell
			
			if(p->getType() != -1) {
				for(int j = 0; j < sizeNeighbours;j++){     //iterate over their neighbours
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

							if( //Direct neighbour
								(std::abs(y-yb) <= 1 && x == xb) ||
								(std::abs(x-xb) <= 1 && y == yb)) {
									forceIJ = (length-r0)*k*factor3/length;
									p->addOnF(forceIJ);
							}else if (std::abs(x-xb) <= 1 && std::abs(y-yb) <= 1 ) {        //diagonal neighbour
								forceIJ = (length-r0sqrt)*k*factor3/length;
								p->addOnF(forceIJ);
							} else {
								if(length >= mindist * p->getSigma() && length <= cutoff){
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


void MemCalc::calculateAll() {
	LOG4CXX_TRACE(loggerCalc, "starting new calculation loop of Membrane Calculation");
	calculateForce();
	calculateVelocity();
	calculatePosition();
	lcDomain->reset();
}

void RayCalc::calculateAll() {
	LOG4CXX_TRACE(loggerCalc, "starting new calculation loop of RayLeighTailor Calculation");
	calculateForce();
	calculatePosition();
	calculateVelocity();
	lcDomain->reset();
}

void Calculation::calculateSingleForce(Particle* p1, Particle* p2){
	double dist = ((p1->getX() -(p2->getX())).L2Norm());
	double factor1 = (24 * p1->getEpsilon())/pow(dist,2);
	double factor2 = pow((p1->getSigma()/dist),6)- (2*pow((p1->getSigma()/dist),12));
	utils::Vector<double,3> factor3 = p2->getX()-p1->getX();
	utils::Vector<double,3> forceIJ = factor1 * factor2 * factor3;
	p1->addOnF(forceIJ);
}
