/*
 * Particle.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "utils/Vector.h"

class Particle {

private:

	/** the position of the particle */
	utils::Vector<double, 3> x;

	/** the velocity of the particle */
	utils::Vector<double, 3> v;

	/** the force effective on this particle */
	utils::Vector<double, 3> f;

	/** the force wich was effective on this particle */
	utils::Vector<double, 3> old_f;

	/** the mass of this particle */
	double m;

	/** type of the particle. Use it for whatever you want (e.g. to seperate
	 * molecules belonging to different bodies, matters, and so on)
	 */
	int type;

	/**
	 * the epsilon parameter of this particle
	 */
	double epsilon;

	/**
	 * the sigma parameter of this particle
	 */
	double sigma;

	int uid;	//unique particle id

public:
	/**
	 * Constructor
	 * @param type
	 */
	Particle(int type = 0);

	/**
	 * Constructer by copying particle
	 * @param other
	 */
	Particle(const Particle& other);

	/**
	 * Constructor with values from exterior data
	 * @param x_arg
	 * @param v_arg
	 * @param m_arg
	 * @param type
	 */
	Particle(
			// for visualization, we need always 3 coordinates
			// -> in case of 2d, we use only the first and the second
			utils::Vector<double, 3> x_arg,
	        utils::Vector<double, 3> v_arg,
	        double m_arg,
	        int type = 0
	);
	/**
	 * Destructor
	 */
	virtual ~Particle();
	/**
	 * Getter for position vector x
	 * @return x
	 */
	inline utils::Vector<double, 3>& getX();

	/**
	 * Sets position vector x
	 * @param x
	 */
	void setX(utils::Vector<double, 3>& x);

	/**
	 * Getter for force vector f
	 * @return f
	 */
	utils::Vector<double, 3>& getF();

	/**
	 * Setter for force vector f
	 * @param newf
	 */
	void setF(utils::Vector<double, 3>& newf);

	/**
	 * Adds tmp vector on actual force vector f
	 * @param tmp
	 */
	void addOnF(utils::Vector<double, 3>& tmp);

	/**
	 * Getter for old_force vector old_f
	 * @return old_f
	 */
	utils::Vector<double, 3>& getOldF();

	/**
	 * Setter for old force vector old_f
	 * @param f
	 */
	void setOldF(utils::Vector<double, 3>& f);

	/**
	 * Getter for velocity vector v
	 * @return v
	 */
	utils::Vector<double, 3>& getV();

	/**
	 * Setter for velocity vector v
	 * @param v
	 */
	void setV(utils::Vector<double, 3>& v);

	/**
	 * Getter for mass m
	 * @return m
	 */
	double getM();

	/**
	 *
	 * @return type
	 */
	int getType();

	/**
	 * == operator
	 * @param other
	 * @return bool
	 */
	bool operator==(Particle& other);

	/**
	 * toString method
	 * @return string
	 */
	std::string toString();
	
	/**
	 * toString method for force vector f only
	 * @return
	 */
	std::string toStringForce();

	/**
	 * computes the distance to another particle in space
	 */
	double getDistanceTo(Particle* part);
	double getDistanceToSq(Particle* part);
	void setM(double m);
	void setType(int type);
	double getEpsilon();
	void setEpsilon(double epsilon);
	double getSigma();
	void setSigma(double sigma);
	void resetForce();
	/**
	 * increases speed by about 1%
	 */
	inline bool approxDist(Particle* part, double cutHalf);
	inline void setUid(int uid_);
	inline int getUid();
};

utils::Vector<double, 3>& Particle::getX() {
	return x;
}

bool Particle::approxDist(Particle* part, double cutHalf) {
	return (std::abs(x[0] - part->getX()[0]) < cutHalf && std::abs(x[1] - part->getX()[1]) < cutHalf);
}


void Particle::setUid(int uid_) {
	uid = uid_;
}

int Particle::getUid() {
	return uid;
}

std::ostream& operator<<(std::ostream& stream, Particle& p);

#endif /* PARTICLE_H_ */
