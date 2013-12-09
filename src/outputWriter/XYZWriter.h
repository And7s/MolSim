/*
 * XYZWriter.h
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#ifndef XYZWRITER_H_
#define XYZWRITER_H_

#include "Particle.h"
#include <fstream>
#include <list>
#include "utils/Vector.h"
#include <cstdlib>
#include <sstream>

namespace outputWriter {

class XYZWriter {

public:
	XYZWriter();

	virtual ~XYZWriter();

	void plotParticles(std::list<Particle> particles, const std::string& filename, int iteration);

};

}

#endif /* XYZWRITER_H_ */
