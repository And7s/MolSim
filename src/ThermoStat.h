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
	ThermoStat(LCDomain* linkedCell, std::auto_ptr<input_t>& inp);
	virtual ~ThermoStat();
	void apply();
	void getTemperature();
	void getTemperatureFlow();
	void multiply(double beta);
	void change();
	void applyFirstEkin();

protected:
	LCDomain* linkedCell;
	int num_Particles, dimensions, num_NotWall_Particles;
	double cur_temp, target_temp, delta_temp, delta_t;
	bool subavg,use_delta_temp, flow;
	utils::Vector<double, 3> avg;


};

#endif /* THERMOSTAT_H_ */
