/*
 * Particle.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "Particle.h"

#include <sstream>
#include <iostream>

using namespace std;

Particle::Particle(int type_arg) {
	type = type_arg;
	//std::cout << "Particle generated!" << std::endl;
	f = 0.0;
	old_f = 0.0;
}

Particle::Particle(const Particle& other) {
	x = other.x;
	v = other.v;
	f = other.f;
	old_f = other.old_f;
	m = other.m;
	type = other.type;
	//std::cout << "Particle generated by copy!" << std::endl;;
}

// Todo: maybe use initializater list instead of copy?
Particle::Particle(	utils::Vector<double, 3> x_arg,
	        utils::Vector<double, 3> v_arg,
	        double m_arg,
	        int type_arg
) {
    x = x_arg;
    v = v_arg;
    m = m_arg;
    type = type_arg;
    f = 0.0;
    old_f = 0.0;
    //std::cout << "Particle generated!" << std::endl;
}

Particle::~Particle() {
	//std::cout << "Particle destructed!" << std::endl;
}

utils::Vector<double, 3>& Particle::getX() {
	return x;
}

void Particle::setX(utils::Vector<double, 3>& newX) {
	x = newX;
}

utils::Vector<double, 3>& Particle::getV() {
	return v;
}

void Particle::setV(utils::Vector<double, 3>& newV) {
	v = newV;
}

utils::Vector<double, 3>& Particle::getF() {
	return f;
}

void Particle::setF(utils::Vector<double, 3>& newF) {
	f = newF;
}

void Particle::addOnF(utils::Vector<double, 3>& tmp) {
	f = f +(tmp);
}

utils::Vector<double, 3>& Particle::getOldF() {
	return old_f;
}

void Particle::setOldF(utils::Vector<double, 3>& newOldF) {
	old_f = newOldF;
}

double Particle::getM() {
	return m;
}

void Particle::setM(double m) {
	this->m = m;
}

int Particle::getType() {
	return type;
}

double Particle::getEpsilon(){
	return epsilon;
}

void Particle::setEpsilon(double epsilon) {
	this->epsilon = epsilon;
}

double Particle::getSigma(){
	return sigma;
}

void Particle::setSigma(double sigma) {
	this->sigma = sigma;
}

void Particle::setType(int type) {
	this->type = type;
}

std::string Particle::toString() {
	std::stringstream stream;
	stream << "x: " << x <<  " v: " << v << " f: " << f << " old_f: " << old_f;
	//stream << x.L2Norm() << " v: "<< v.L2Norm() << "f: "<<f.L2Norm();
	return stream.str();
}

std::string Particle::toStringForce() {
	std::stringstream stream;
	stream << " f: " << f;
	//stream << x.L2Norm() << " v: "<< v.L2Norm() << "f: "<<f.L2Norm();
	return stream.str();
}

bool Particle::operator ==(Particle& other) {
	if ( (x == other.x) && (v == other.v) && (f == other.f) &&
			((type == other.type) & (m == other.m)) && (old_f == other.old_f)) {
		return true;
	}

	return false;
}

std::ostream& operator<<(std::ostream& stream, Particle& p) {
	stream << p.toString();
	return stream;
}

double Particle::getDistanceTo(Particle* part) {
	return std::sqrt(
				std::pow(this->x[0] - part->getX()[0],2) +
				std::pow(this->x[1] - part->getX()[1],2) +
				std::pow(this->x[2] - part->getX()[2],2));
}
