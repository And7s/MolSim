/*
 * FileReader.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "FileReader.h"
#include "utils/Vector.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace std;

/**
 * Logger
 */
LoggerPtr loggerFile(Logger::getLogger( "main.file"));

FileReader::FileReader() {
}

FileReader::~FileReader() {
}


void FileReader::readFile(std::list<Particle>& particles, char* filename) {
	double x[] = {0,0,0};
	double v[] = {1,1,1};
	double m = 1;
    int num_particles = 0;

    std::ifstream input_file(filename);
    string tmp_string;

    if (input_file.is_open()) {

    	getline(input_file, tmp_string);
    	LOG4CXX_TRACE(loggerFile, "Read line: " << tmp_string);

    	while (tmp_string.size() == 0 || tmp_string[0] == '#') {
    		getline(input_file, tmp_string);
    		LOG4CXX_TRACE(loggerFile, "Read line: " << tmp_string);
    	}

    	istringstream numstream(tmp_string);
    	numstream >> num_particles;
    	LOG4CXX_TRACE(loggerFile, "Reading " << num_particles << ".");
    	getline(input_file, tmp_string);
    	LOG4CXX_TRACE(loggerFile, "Read line: " << tmp_string);

    	for (int i = 0; i < num_particles; i++) {
    		istringstream datastream(tmp_string);

    		for (int j = 0; j < 3; j++) {
    			datastream >> x[j];

    		}
    		for (int j = 0; j < 3; j++) {
    			datastream >> v[j];
    		}
    		if (datastream.eof()) {
    			LOG4CXX_FATAL(loggerFile, "Error reading file: eof reached unexpectedly reading from line " << i << " Program will halt!");
    			exit(-1);
    		}
    		datastream >> m;
    		Particle p(x, v, m);
    		particles.push_back(p);

    		getline(input_file, tmp_string);
    		LOG4CXX_TRACE(loggerFile, "Read line: " << tmp_string);
    	}
    } else {
    	LOG4CXX_FATAL(loggerFile, "Error: could not open file " << filename << " Program will halt");
    	exit(-1);
    }
}

