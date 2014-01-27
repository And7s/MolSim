/*
 * CSVWriter.h
 *
 *  Created on: Jan 23, 2014
 *      Author: friedrich
 */

#ifndef CSVWRITER_H_
#define CSVWRITER_H_

#include "Particle.h"
#include "LCDomain.h"
#include <fstream>
#include <list>
#include "utils/Vector.h"
#include <cstdlib>
#include <sstream>
#include <stdlib.h>

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

namespace outputWriter {
/*
 *
 */
class CSVWriter {
public:
	CSVWriter();

	CSVWriter(int dimension_, int bins_);
	virtual ~CSVWriter();

	void writeFile(std::vector<Particle*> particles);

private:
	int bins;
	int dimension;
};

}
#endif /* CSVWRITER_H_ */
