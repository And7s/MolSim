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

		void XVFWriter::writeFile(std::vector<Particle*> particles, const std::string& filename){
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
				"# * xyz-coordinates (3 double values)\n"
				"# * velocities (3 double values)\n"
		    	"# * old_force (3 double values)\n"
		    	"# * force (3 double values)\n"
				"# * mass (1 double value)\n"
		    	"# * type (1 int value)\n"
				"#\n"
				"# xyz-coord             velocity        force             old_force       mass     type" << std::endl;


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
					output_file << particles[i]->getType() << std::endl;

					/*
					getline(output_file, tmp_string);
					cout << "Read line: " << tmp_string << endl;

					while (tmp_string.size() == 0 || tmp_string[0] == '#') {
						getline(input_file, tmp_string);
						cout << "Read line: " << tmp_string << endl;
					}

					istringstream numstream(tmp_string);
					numstream >> num_particles;
					cout << "Reading " << num_particles << "." << endl;
					getline(input_file, tmp_string);
					cout << "Read line: " << tmp_string << endl;

					for (int i = 0; i < num_particles; i++) {
						istringstream datastream(tmp_string);

						for (int j = 0; j < 3; j++) {
							datastream >> x[j];

						}
						for (int j = 0; j < 3; j++) {
							datastream >> v[j];
						}
						for (int j = 0; j < 3; j++) {
							datastream >> oldF[j];

						}
						for (int j = 0; j < 3; j++) {
							datastream >> f[j];

						}

						if (datastream.eof()) {
							cout << "Error reading file: eof reached unexpectedly reading from line " << i << endl;
							exit(-1);
						}
						datastream >> m;
						datastream >> type;
						Particle* p = new Particle(x,v,m);
						p->setF(f);
						p->setOldF(oldF);
						p->setType(type);
						particles.push_back(p);

						getline(input_file, tmp_string);
						cout << "Read line: " << tmp_string << endl;
					}*/
					}
		    } else {
		    	std::cout << "Error: could not open file " << filename << std::endl;
		    	exit(-1);
		    }
		}
}

