/*
 * XVFWriter.cpp
 *
 *  Created on: Dec 9, 2013
 *      Author: friedrich
 */

#include "outputWriter/XVFWriter.h"


namespace outputWriter {
		XVFWriter::XVFWriter() {
			// TODO Auto-generated constructor stub

		}

		XVFWriter::~XVFWriter() {
			// TODO Auto-generated destructor stub
		}


		std::vector<Particle*> XVFWriter::readFile(std::vector<double>* parameters, const std::string& filename) {
			double x[] = {0,0,0};
			double v[] = {1,1,1};
			double old_F[] = {0,0,0};
			double f_[] = {0,0,0};
			utils::Vector<double, 3> oldF = old_F;
			utils::Vector<double, 3> f = f_;
			double m = 1;
			double sigma = -1;
			double epsilon = -1;
			int type = 0;
			int nature = -1;
			int num_particles = 0;
			std::vector<Particle*> particles;

			std::stringstream strstr;
			strstr << filename;
			std::ifstream input_file(strstr.str().c_str());
			std::string tmp_string;

			if (input_file.is_open()) {

				getline(input_file, tmp_string);

				while (tmp_string.size() == 0 || tmp_string[0] == '#') {
					getline(input_file, tmp_string);
				}

				std::istringstream numstream(tmp_string);
				numstream >> num_particles;
				//delta_t
				getline(input_file, tmp_string);
				(*parameters).push_back(atof(tmp_string.c_str()));
				//cutOff
				getline(input_file, tmp_string);
				(*parameters).push_back(atof(tmp_string.c_str()));
				//gravity
				getline(input_file, tmp_string);
				(*parameters).push_back(atof(tmp_string.c_str()));
				//first line of data
				getline(input_file, tmp_string);

				for (int i = 0; i < num_particles; i++) {
					std::istringstream datastream(tmp_string);

					for (int j = 0; j < 3; j++) {
						datastream >> x[j];
					}
					for (int j = 0; j < 3; j++) {
						datastream >> v[j];
					}
					for (int j = 0; j < 3; j++) {
						datastream >> f[j];
					}
					for (int j = 0; j < 3; j++) {
						datastream >> oldF[j];
					}

					if (datastream.eof()) {
						std::cout << "Error reading file: eof reached unexpectedly reading from line " << i << std::endl;
						exit(-1);
					}
					datastream >> m;
					datastream >> epsilon;
					datastream >> sigma;
					datastream >> type;
					datastream >> nature;
					Particle* p = new Particle(x,v,m);
					p->setF(f);
					p->setOldF(oldF);
					p->setEpsilon(epsilon);
					p->setSigma(sigma);
					p->setType(type);
					p->setNature(nature);
					particles.push_back(p);

					getline(input_file, tmp_string);
				}
			} else {
				std::cout << "Error: could not open file " << filename << std::endl;
				exit(-1);
			}
			return particles;
		}

		void XVFWriter::writeFile(std::vector<Particle*> particles, const std::string& filename, std::vector<double>& parameters){
			std::stringstream strstr;
			strstr << filename << ".txt";
		    std::ofstream output_file(strstr.str().c_str());
		    std::string tmp_string;

		    if (output_file.is_open()) {
		    	std::vector<Particle*>::iterator iterator = particles.begin();
		    	output_file <<
		    	"#\n"
				"# file format:\n"
				"# Lines of comment start with '#' and are only allowed at the beginning of the file\n"
				"# Empty lines are not allowed.\n"
				"# The first line not being a comment has to be one integer, indicating the number of\n"
				"# molecule data sets.\n"
				"#\n"
				"# Molecule data consists of\n"
		    	"# 		Parameters:\n"
		    	"# * numberOfParticles \n"
		        "# * delta_t \n"
		    	"# * cutOff \n"
		    	"# * gravity \n"
				"# * xyz-coordinates (3 double values)\n"
				"# * velocities (3 double values)\n"
		    	"# * old_force (3 double values)\n"
		    	"# * force (3 double values)\n"
				"# * mass (1 double value)\n"
		    	"# * type (1 int value)\n"
				"#\n"
				"# xyz-coord             velocity        force             old_force       mass    epsilon    sigma     type     nature" << std::endl;


		    	output_file << particles.size() << std::endl;
		    	output_file << parameters[0] << std::endl;
		    	output_file << parameters[1] << std::endl;
		    	output_file << parameters[2] << std::endl;

		    	for(int i = 0; i<particles.size(); i++){
					for (int j = 0; j < 3; j++) {
						output_file << particles[i]->getX()[j] << " ";
					}
					output_file << "\t";
					for (int j = 0; j < 3; j++) {
						output_file << particles[i]->getV()[j] << " ";
					}
					output_file << "\t";
					for (int j = 0; j < 3; j++) {
						output_file << particles[i]->getF()[j] << " ";
					}
					output_file << "\t";
					for (int j = 0; j < 3; j++) {
						output_file << particles[i]->getOldF()[j] << " ";
					}
					output_file << "\t";
					output_file << particles[i]->getM() << " ";
					output_file << "\t";
					output_file << particles[i]->getEpsilon() << " ";
					output_file << "\t";
					output_file << particles[i]->getSigma() << " ";
					output_file << "\t";
					output_file << particles[i]->getType() << std::endl;
					output_file << "\t";
					output_file << particles[i]->getNature() << std::endl;
					}
		    } else {
		    	std::cout << "Error: could not open file " << filename << std::endl;
		    	exit(-1);
		    }
		}
}

