/*
 * ThermoStat.h
 *
 *  Created on: Jan 23, 2014
 *      Author: friedrich
 */

#ifndef THERMOSTAT_H_
#define THERMOSTAT_H_

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include "MaxwellBoltzmannDistribution.h"

#include "LCDomain.h"

#include <memory>
#include <iostream>
#include "input.h"

/*
 *
 */
class ThermoStat {
public:
	/**
	 * Constructor which applies also firstEkin
	 * @param linkedCell
	 * @param inp
	 */
	ThermoStat(LCDomain* linkedCell, std::auto_ptr<input_t>& inp);

	virtual ~ThermoStat();

	/**
	 * Function to apply the Thermostat, by first calculating the current temperature
	 * and calculating beta with it
	 */
	void apply();

	/**
	 * Function to calculate the current temperature with the kinetic energy of the system
	 */
	void getTemperature();

	/**
	 * Function to calculate the current temperature with the kinetic energy of the system
	 * without the y-Direction as described in Sheet5 Task4
	 */
	void getTemperatureFlow();

	/**
	 * Function to calculate the starting Velocity with the given initial Temperature via the
	 * kinetic Energy
	 */
	void applyFirstEkin();

protected:
	LCDomain* linkedCell;
	int num_Particles, dimensions, num_NotWall_Particles;
	double cur_temp, target_temp, delta_temp, delta_t;
	bool subavg,use_delta_temp, flow;
	utils::Vector<double, 3> avg;


};

#endif /* THERMOSTAT_H_ */
