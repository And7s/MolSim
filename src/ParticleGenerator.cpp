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

struct Cuboid {
	double 
		pos[3],
		dist,
		mass,
		vel[3];
	int num[3];
};

Particle** ParticleGenerator::readFile(char* filename, int* length) {
	LOG4CXX_TRACE(loggerPG, "ParticleGenerator to open File: " << filename);
	
	int num_particles = 0;
	int num_cuboid = 0;

	Cuboid* ca;    

	std::ifstream input_file(filename);
	string tmp_string;

	if (input_file.is_open()) {
		getline(input_file, tmp_string);

		while (tmp_string.size() == 0 || tmp_string[0] == '#') {
			getline(input_file, tmp_string);
			LOG4CXX_TRACE(loggerPG, "Read line: " << tmp_string);

		}
		

		istringstream numstream(tmp_string);
		numstream >> num_cuboid;
		LOG4CXX_TRACE(loggerPG, "Reading " << num_cuboid << "Cuboids.");
		ca = new Cuboid[num_cuboid];


		for (int i = 0; i < num_cuboid; i++) {
			
		   getline(input_file, tmp_string);
		   LOG4CXX_TRACE(loggerPG, "Read line: " << i << ": " << tmp_string);
		   istringstream datastream(tmp_string);
		   for (int j = 0; j < 3; j++) {
			   datastream >> ca[i].pos[j];
		   }
		   for (int j = 0; j < 3; j++) {
			   datastream >> ca[i].num[j];
		   }
		   datastream >> ca[i].dist >> ca[i].mass;

		   for (int j = 0; j < 3; j++) {
			   datastream >> ca[i].vel[j];
		   }

		   	//validity checks
			for(int j = 0; j < 3; j++) {
				if(ca[i].num[j] < 0) {
					LOG4CXX_FATAL(loggerPG, "Error: Count of cuboids cant be negative. Got number: "<<ca[i].num[j]);
					exit(-1);
				}
				
			}
			if(ca[i].mass < 0) {
				LOG4CXX_FATAL(loggerPG, "Error: Mass of cuboids cant be negative. Got number: "<<ca[i].mass);
				exit(-1);
			}


		}
	} else {
		LOG4CXX_FATAL(loggerPG, "Error: could not open file " << filename << " Program will halt");
		exit(-1);
	}




	for(int i = 0; i < num_cuboid; i++) {
		num_particles += ca[i].num[0] * ca[i].num[1] * ca[i].num[2];
	}


	Particle** pa = new Particle*[num_particles];

	double x[] = {0,0,0};
	double v[] = {1,1,1};
	double m = 1;

	int num = 0;
	for(int i = 0; i < num_cuboid; i++) {
		v[0] = ca[i].vel[0];
		v[1] = ca[i].vel[1];
		v[2] = ca[i].vel[2];
		m = ca[i].mass;
		for(int d1 = 0; d1 < ca[i].num[0]; d1++) {
			x[0] = d1*ca[i].dist+ca[i].pos[0];
			for(int d2 = 0; d2 < ca[i].num[1]; d2++) {
				x[1] = d2*ca[i].dist+ca[i].pos[1];
				for(int d3 = 0; d3 < ca[i].num[2]; d3++) {
					x[2] = d3*ca[i].dist+ca[i].pos[2];
					pa[num] = new Particle(x,v,m);
					utils::Vector<double, 3> velo = v;
					MaxwellBoltzmannDistribution(*pa[num],velo.L2Norm(),3);
					num++;
				}
			}
		}
	}
	delete[] ca;
	ca = 0;
	*length =num_particles;
	return pa;
}

