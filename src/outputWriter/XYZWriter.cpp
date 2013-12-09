/*
 * XYZWriter.cpp
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#include "outputWriter/XYZWriter.h"

using namespace std;

namespace outputWriter {

XYZWriter::XYZWriter() {
	// TODO Auto-generated constructor stub

}

XYZWriter::~XYZWriter() {
	// TODO Auto-generated destructor stub
}

void XYZWriter::plotParticles(std::list<Particle> particles, const std::string& filename, int iteration) {
	std::ofstream file;
	stringstream strstr;
	strstr << filename << "_" << (iteration < 10 ? "000" : (iteration < 100 ? "00" : ( iteration < 1000 ? "0" : "") )) << iteration << ".xyz";

	file.open(strstr.str().c_str());
	file << particles.size() << endl;
	file << "Generated by MolSim. See http://openbabel.org/wiki/XYZ_(format) for file format doku." << endl;

	list<Particle>::iterator iterator = particles.begin();
	while (iterator != particles.end()) {
		Particle& p = *iterator;
		utils::Vector<double, 3> x = p.getX();
		file << "Ar ";
		file.setf(ios_base::showpoint);

		for (int i = 0; i < 3; i++) {
			file << x[i] << " ";
		}

		file << endl;
		iterator++;
	}

	file.close();
}

} // end namespace
