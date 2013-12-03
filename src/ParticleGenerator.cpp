/**
 * Particle Generator
 * Creates Particels in the shape of cuboids according to a given input file
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */

#include "ParticleGenerator.h"

/**
 * Logger
 */
LoggerPtr loggerPG(Logger::getLogger( "main.PG"));


ParticleGenerator::ParticleGenerator() {
}

ParticleGenerator::~ParticleGenerator() {}


std::vector<Particle*> ParticleGenerator::readFile(int* length, auto_ptr<input_t>& inp) {
	LOG4CXX_TRACE(loggerPG, "ParticleGenerator called to generate particles");
	
	int num_particles = 0;

	for (input_t::cuboid_const_iterator ci (inp->cuboid ().begin ());ci != inp->cuboid ().end ();++ci){
		num_particles += ci->number().x() * ci->number().y() * ci->number().z();
    }
	std::vector<Particle*> pa;
	Particle* p;

	double x[] = {0,0,0};
	double v[] = {1,1,1};

	int num = 0;
	for (input_t::cuboid_const_iterator ci (inp->cuboid ().begin ());ci != inp->cuboid ().end ();++ci){
		v[0] = ci->velocity().x();
		v[1] = ci->velocity().y();
		v[2] = ci->velocity().z();

		for(int d1 = 0; d1 < ci->number().x(); d1++) {
			x[0] = d1*ci->distance()+ci->position().x();
			for(int d2 = 0; d2 < ci->number().y(); d2++) {
				x[1] = d2*ci->distance()+ci->position().y();
				for(int d3 = 0; d3 < ci->number().z(); d3++) {
					x[2] = d3*ci->distance()+ci->position().z();
					pa.push_back(new Particle(x,v,ci->mass()));
					utils::Vector<double, 3> velo = v;
					MaxwellBoltzmannDistribution(*(pa[num]),velo.L2Norm(),2);
					num++;
				}
			}
		}
	}
	
	*length =num_particles;
	return pa;
}

