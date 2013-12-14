
/*
 * Thermostats.h
 * Forces to run the Molecular Simulation at a certain rising or decreasing temperature.
 * 9-12-2013
 * Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
*/


#ifndef THERMOSTATS_H
#define THERMOSTATS_H

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include "MaxwellBoltzmannDistribution.h"

#include "LCDomain.h"

#include <memory>
#include <iostream>
#include "input.h"


class Thermostat {
	protected:
	LCDomain* linkedCell;
	int num_Particles, dimensions;
	float cur_temp, target_temp, delta_temp;
	bool subavg;
	utils::Vector<double, 3> avg;

	public:
		Thermostat(LCDomain* linkedCell, std::auto_ptr<input_t>& inp);
		~Thermostat();
		void apply();
		double getEkin();
		void multiply(double beta);
		void change();

};

#endif