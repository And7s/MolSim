/*
 * EnvironmentalInfluences.cpp
 *
 *  Created on: Dec 8, 2013
 *      Author: paul
 */

#include "EnvInfl.h"

LoggerPtr loggerEnv(Logger::getLogger("main.env"));

EnvInfl* EnvInfl::instance = NULL;

EnvInfl::EnvInfl() {
}

EnvInfl::~EnvInfl() {
}

EnvInfl* EnvInfl::getInstance(){
	if(instance == NULL){
		instance = new EnvInfl();
	}
	return instance;
}

void EnvInfl::destroy(){
	if(instance != NULL){
		delete instance;
	}
	instance = NULL;
}

void EnvInfl::setG(double g){
	this->g = g;
}

double EnvInfl::getG(){
	return this->g;
}

/**
 * gravity in -y direction
 */
void EnvInfl::calculateGravity(Particle* part){
	//std::cerr << "ENV infl\n";
	utils::Vector<double,3> force;
	force[0] = 0 * part->getM() * this->g;
	force[1] = 1 * part->getM() * this->g;
	force[2] = 0 * part->getM() * this->g;
//std::cerr <<force<<"\n";
//LOG4CXX_ERROR(loggerEnv, "F: "<<force[0]<<" "<<force[1]<< " "<<force[2]);

	part->addOnF(force);
}

void EnvInfl::calculateSpecParts(int timestep){
	int size = specParts.size();
	for(int i = 0; i < size; i++){
		specParts[i]->adjustForce(timestep);
	}
}

void EnvInfl::addSpecPart(double startTime, double endTime,
		std::vector<double> force, bool relative, Particle* part) {
	SpecializedParticle* sp = new SpecializedParticle(part);
	sp->setStartTime(startTime);
	sp->setEndTime(endTime);
	sp->setConstForce(force,relative);
	this->specParts.push_back(sp);
}
