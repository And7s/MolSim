/*
 * Thermostats 
 * Forces to run the Molecular Simulation at a certain rising or decreasing temperature.
 * 9-12-2013
 * Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
*/

#include "Thermostat.h"


using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace std;

LoggerPtr loggerThermostat(Logger::getLogger( "main.thermostat"));

Thermostat::Thermostat(LCDomain* linkedCell_, auto_ptr<input_t>& inp) {
 	linkedCell = linkedCell_;
 	num_Particles = 0;
 	dimensions = inp->dimensions();
 	cur_temp = inp->Thermostats().initial_temp();
 	delta_temp = inp->Thermostats().delta_temp();
 	target_temp = inp->Thermostats().target_temp();
	subavg = false;	//whether the avg velocity is subtracted or not
	LOG4CXX_INFO(loggerThermostat, "Initializing Thermostat at temperature "<<cur_temp);
 	
 	ASSERT_WITH_MESSAGE(loggerThermostat, delta_temp > 0, "Delta Temp must be greater 0");

 	if(inp->Thermostats().applied_after() == 0){
 		apply();
 	}
}

/*will return the current kinetic Energy and calculate num_particles as well*/
double Thermostat::getEkin() {
	int size = linkedCell->getNumberOfCells();
	double Ekin = 0;
	Particle* p;
	ParticleContainer** pcArray = linkedCell->getCells();
	num_Particles = 0;	//recalc the number of particles as well
	utils::Vector<double, 3> tmp;
	
	avg = avg*0;//reset avg
	
	for(int i = 0;i < size;i++){
		int j=0;
		while((p = pcArray[i]->nextParticle(&j)) != NULL){
			tmp = p->getV();
			avg = avg+ tmp;	
			num_Particles++;
		}
	}
	avg = avg/num_Particles;
	num_Particles = 0;
	//cout << "Sum of avg"<<avg[0]<<" "<<avg[1]<< " "<< avg[2] <<"\n";

	for(int i = 0;i < size;i++){
		int j=0;
		while((p = pcArray[i]->nextParticle(&j)) != NULL){
			tmp = p->getV();
			if(subavg) {
				Ekin += (tmp-avg).NormSq();
			}else {
				Ekin += tmp.NormSq();
			}
			
			num_Particles++;
		}
	}
	Ekin *= 0.5;

	return Ekin;
}

void Thermostat::apply() {
	double Ekin = getEkin();
	ASSERT_WITH_MESSAGE(loggerThermostat, Ekin > 0, "Ekin mustn't be 0");

	double Ekind = num_Particles*dimensions/2*cur_temp;
	double beta = sqrt(Ekind / Ekin);
	//LOG4CXX_TRACE(loggerThermostat, "apply Temperature"<<cur_temp<<" by faktor"<<beta);

	multiply(beta);

}


//helper function which multiplys all particles by a given multiplicator
void Thermostat::multiply(double beta) {
	if(beta == 1) {	//save time, dont calc
		return;
	}
	
	int size = linkedCell->getNumberOfCells();
	ParticleContainer** pcArray = linkedCell->getCells();
	Particle* p;
	for(int i = 0;i < size;i++){
		int j=0;
		while((p = pcArray[i]->nextParticle(&j)) != NULL){
			utils::Vector<double, 3> newvel;
			if(subavg) {
				newvel = (p->getV()-avg)*beta+avg;
			}else {
				newvel = p->getV()*beta;
			}
			
			p->setV(newvel);		
		}
	}

}


void Thermostat::change() {
	if(target_temp == cur_temp) return;	//already reached
	if(target_temp < cur_temp) {	//decreasing
		if(cur_temp-target_temp < delta_temp) {	//reaching goal under delta step
			cur_temp = target_temp;
		}else {
			cur_temp -= delta_temp;
		}
	}else {	//rising
		if(target_temp-cur_temp < delta_temp) {
			cur_temp = target_temp;
		}else {
			cur_temp += delta_temp;
		}
	}
	LOG4CXX_INFO(loggerThermostat, "Changed Temperatur to "<<cur_temp);
}
