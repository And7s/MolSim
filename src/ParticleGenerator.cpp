/**
 * Particle Generator
 */

#include "ParticleGenerator.h"
#include "Particle.h"
#include "utils/Vector.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;

ParticleGenerator::ParticleGenerator() {
}

ParticleGenerator::~ParticleGenerator() {
}

struct Cuboid {
	double 
		pos[3],
		dist,
		mass,
		vel[3];
	int num[3];
};

Particle** ParticleGenerator::readFile(char* filename, int* length) {
	cout << "ParticleGenerator call"<<filename;

	
    int num_particles = 0;
    int num_cuboid = 0;
   

    

    Cuboid* ca;
    

    std::ifstream input_file(filename);
    string tmp_string;

    if (input_file.is_open()) {

    	getline(input_file, tmp_string);
    	//cout << "Read line: " << tmp_string << endl;

    	while (tmp_string.size() == 0 || tmp_string[0] == '#') {
    		getline(input_file, tmp_string);
    		cout << "Read line: " << tmp_string << endl;
    	}
    	

    	istringstream numstream(tmp_string);
    	numstream >> num_cuboid;

    	cout << "Reading " << num_cuboid << "Cuboids ." << endl;
    	ca = new Cuboid[num_cuboid];
    	
    	//getline(input_file, tmp_string);
    	//cout << "Read line: " << tmp_string << endl;

    	for (int i = 0; i < num_cuboid; i++) {
    		
    	getline(input_file, tmp_string);
    	cout  << "Read line: "<<i<<":"<< tmp_string << endl;
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

    	}
    } else {
    	std::cout << "Error: could not open file " << filename << std::endl;
    	exit(-1);
    }

    //file read now create particles
    cout << ca[0].num[0] << ca[0].num[1] << ca[0].num[2] << endl;
    for(int i = 0; i < num_cuboid; i++) {
        cout << "add"<<(ca[i].num[0] * ca[i].num[1] * ca[i].num[2])<<endl;
    	num_particles += ca[i].num[0] * ca[i].num[1] * ca[i].num[2];
    }

    cout << "num particles: "<< num_particles;
 	typedef Particle* PartPtr;
    PartPtr* pa = new PartPtr[num_particles];

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
    				cout << num << " = "<<pa[num]->toString()<<endl;
					num++;
    			}
    		}
    	}
    }

    *length =num_particles;

    return pa;


}

