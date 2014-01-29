/*
 * XVFWriter.h
 *
 *  Created on: Dec 9, 2013
 *      Author: andreas,paul,friedrich
 */

#ifndef XVFWRITER_H_
#define XVFWRITER_H_

#include <vector>
#include <fstream>
#include <list>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

#include "Particle.h"
#include "utils/Vector.h"
/*
 *
 */
namespace outputWriter {
class XVFWriter {
	public:
	XVFWriter();
	virtual ~XVFWriter();

	std::vector<Particle*> readFile(std::vector<double>* parameters, const std::string&  filename, int* uid);

	void writeFile(std::vector<Particle*> particles, const std::string& filename, std::vector<double>& parameters);
	};
}

#endif /* XVFWRITER_H_ */
