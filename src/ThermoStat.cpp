/*
 * ThermoStat.cpp
 *
 *  Created on: Jan 23, 2014
 *      Author: friedrich
 */

#include "ThermoStat.h"

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace std;

LoggerPtr loggerThermostat(Logger::getLogger( "main.thermostat"));

ThermoStat::ThermoStat(LCDomain* linkedCell_, auto_ptr<input_t>& inp) {
 	linkedCell = linkedCell_;
 	num_Particles = 0;
 	num_NotWall_Particles = 0;
 	dimensions = inp->dimensions();
 	cur_temp = inp->Thermostats().initial_temp();
 	delta_temp = inp->Thermostats().delta_temp();
 	target_temp = inp->Thermostats().target_temp();
 	delta_t = inp->delta_t();
	subavg = false;	//whether the avg velocity is subtracted or not
	flow = true;
	if(abs(target_temp-cur_temp) > delta_temp){
		use_delta_temp = true;
	}else{
		use_delta_temp = false;
	}
	LOG4CXX_INFO(loggerThermostat, "Initializing Thermostat at temperature "<<cur_temp);

 	ASSERT_WITH_MESSAGE(loggerThermostat, delta_temp > 0, "Delta Temp must be greater 0");

 	if(inp->Thermostats().applied_after() == 0){
 		apply();
 	}
 	applyFirstEkin();
}

ThermoStat::~ThermoStat() {
	// TODO Auto-generated destructor stub
}

void ThermoStat::applyFirstEkin(){
	double Ekin = 0;
	//double boltzmann_konst = 1.380648813*pow(10,-23);
	double v = 0;
	Particle* p;
	std::vector<Particle*>* particles = linkedCell->getAllParticles();
	num_Particles = particles->size();
	for(int i = 0;i < num_Particles;i++){
		p = (*particles)[i];
		if(p->getNature()!=2){
			num_NotWall_Particles++;
		}
	}
	Ekin = (num_NotWall_Particles*dimensions/2)*cur_temp;
	std::cout << "In ApplyFirst Ekin: " << num_NotWall_Particles << " " << Ekin << std::endl;
	v = sqrt(2*Ekin/(dimensions*num_NotWall_Particles*1));
	std::cout << "In ApplyFirst v: " << v << std::endl;
	for(int i = 0;i < num_Particles;i++){
		p = (*particles)[i];
		if(p->getNature()!=2){
			MaxwellBoltzmannDistribution(*p,v,3, flow);
		}
	}
}

void ThermoStat::apply(){
	std::vector<Particle*>* particles = linkedCell->getAllParticles();
	num_Particles = particles->size();
	num_NotWall_Particles = 0;
	Particle* p;
	double beta=1;
	for(int i = 0;i < num_Particles;i++){
		p = (*particles)[i];
		if(p->getNature()!=2){
			num_NotWall_Particles++;
		}
	}
	LOG4CXX_INFO(loggerThermostat, "Num_Particles: "<<num_Particles <<" Not_Wall: "<<num_NotWall_Particles);
	utils::Vector<double, 3> tmp;
	if(flow){
		getTemperatureFlow();
	}else{
		getTemperature();
	}
	if(use_delta_temp){
		if(target_temp-cur_temp<delta_temp){
			beta = sqrt((cur_temp-delta_temp)/cur_temp);
		}else if(target_temp-cur_temp>delta_temp){
			beta = sqrt((cur_temp+delta_temp)/cur_temp);
		}else{
			beta = sqrt(target_temp/cur_temp);
		}
	}else{
		//double beta = sqrt(1.0+delta_t*100*((target_temp/cur_temp)-1.0));
		beta = sqrt(target_temp/cur_temp);
	}

	LOG4CXX_INFO(loggerThermostat, "Apply Temperature"<<target_temp<<" by faktor: "<<beta);
	for(int i = 0;i < num_Particles;i++){
		p = (*particles)[i];
		if(p->getNature()!=2){
			if(flow){
				tmp = p->getV();
				tmp[0] = tmp[0] * beta;
				tmp[2] = tmp[2] * beta;
			}else{
				tmp = p->getV() * beta;
			}
			p->setV(tmp);
		}
	}

}

void ThermoStat::getTemperature(){
	double Ekin = 0;
	Particle* p;
	std::vector<Particle*>* particles = linkedCell->getAllParticles();
	utils::Vector<double, 3> tmp;

	for(int i = 0;i < num_Particles;i++){
		p = (*particles)[i];
		if(p->getNature()!=2){
			tmp = p->getV();
			Ekin += (tmp.NormSq()*(p->getM()))*0.5;
		}
	}
	cur_temp = (2*Ekin)/(dimensions*num_NotWall_Particles);
	LOG4CXX_INFO(loggerThermostat, "Cur_temp"<<cur_temp);
}

void ThermoStat::getTemperatureFlow(){
	double Ekin = 0;
	double meanY = 0;
	Particle* p;
	std::vector<Particle*>* particles = linkedCell->getAllParticles();
	utils::Vector<double, 3> tmp;

	for(int i = 0;i < num_Particles;i++){
		p = (*particles)[i];
		if(p->getNature()!=2){
			meanY = meanY + p->getV()[1];
		}
	}
	meanY = meanY/num_NotWall_Particles;

	for(int i = 0;i < num_Particles;i++){
		p = (*particles)[i];
		if(p->getNature()!=2){
			tmp = p->getV();
			tmp[1] = tmp[1]-meanY;
			Ekin += (tmp.NormSq()*(p->getM()))*0.5;
		}
	}
	cur_temp = (2*Ekin)/(dimensions*num_NotWall_Particles);
	LOG4CXX_INFO(loggerThermostat, "Cur_temp"<<cur_temp);
}
