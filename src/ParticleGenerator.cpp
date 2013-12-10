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
	
std::vector<Particle*> partlist;

	float dist = 0;
	double x[] = {0,0,0};
	double v[] = {1,1,1};
	int type = -1;
	double epsilon = -1.0;
	double sigma = -1.0;
	for(input_t::sphere_const_iterator si (inp->sphere().begin()); si != inp->sphere().end(); ++si) {
		float max_dist = std::pow(si->radius(), 2); 
		v[0] = si->velocity().x();
		v[1] = si->velocity().y();
		v[2] = si->velocity().z();
		type = si->type();
		epsilon = si->epsilon();
		sigma = si->sigma();
		LOG4CXX_INFO(loggerPG, "Generate a Sphere");
	    ASSERT_WITH_MESSAGE(loggerPG, (epsilon>0), "Invalid epsilon. Please specify first " << epsilon);
	    ASSERT_WITH_MESSAGE(loggerPG, (sigma>0), "Invalid delta_t. Please specify first " << sigma);
					
		for(float d1 = si->position().x()-si->radius()*si->distance(); d1 < si->position().x()+si->radius()*si->distance(); d1+=si->distance()) {
			x[0] = d1;
			for(float d2 = si->position().y()-si->radius()*si->distance(); d2 < si->position().y()+si->radius()*si->distance(); d2 +=si->distance()) {
				x[1] = d2;
				float d3 = si->position().z();
				x[2] = d3;
				dist = 
					std::pow(si->position().x()-d1,2)+
					std::pow(si->position().y()-d2,2)+
					std::pow(si->position().z()-d3,2);
				if(dist <= max_dist) {
					Particle* p = new Particle(x,v,si->mass());

					p->setType(type);
					p->setEpsilon(epsilon);
					p->setSigma(sigma);
					utils::Vector<double, 3> velo = v;
					MaxwellBoltzmannDistribution(*p,velo.L2Norm(),inp->dimensions());

					partlist.push_back(p);
				}
			}
		}
	}
	LOG4CXX_INFO(loggerPG, "Generated " << partlist.size() << " Particles for Spheres");
	int num_particles = 0;

	for (input_t::cuboid_const_iterator ci (inp->cuboid ().begin ());ci != inp->cuboid ().end ();++ci){
		num_particles += ci->number().x() * ci->number().y() * ci->number().z();
    }
	
	for (input_t::cuboid_const_iterator ci (inp->cuboid ().begin ());ci != inp->cuboid ().end ();++ci){
		v[0] = ci->velocity().x();
		v[1] = ci->velocity().y();
		v[2] = ci->velocity().z();
		type = ci->type();
		epsilon = ci->epsilon();
		sigma = ci->sigma();
	    LOG4CXX_INFO(loggerPG, "Generate Cuboids");
	    ASSERT_WITH_MESSAGE(loggerPG, (epsilon>0), "Invalid epsilon. Please specify first " << epsilon);
	    ASSERT_WITH_MESSAGE(loggerPG, (sigma>0), "Invalid delta_t. Please specify first " << sigma);

		for(int d1 = 0; d1 < ci->number().x(); d1++) {
			x[0] = d1*ci->distance()+ci->position().x();
			for(int d2 = 0; d2 < ci->number().y(); d2++) {
				x[1] = d2*ci->distance()+ci->position().y();
				for(int d3 = 0; d3 < ci->number().z(); d3++) {
					x[2] = d3*ci->distance()+ci->position().z();

					Particle* p = new Particle(x,v,ci->mass());

					p->setType(type);
					p->setEpsilon(epsilon);
					p->setSigma(sigma);
					utils::Vector<double, 3> velo = v;
					MaxwellBoltzmannDistribution(*p,velo.L2Norm(),inp->dimensions());

					partlist.push_back(p);
				}
			}
		}
	}


	LOG4CXX_INFO(loggerPG, "Generated overall " << partlist.size() << " Particles");
	
	*length =partlist.size();
	return partlist;
}


