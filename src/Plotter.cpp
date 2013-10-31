/*
This class represents a strategy pattern, which can switch between the chosen output method.

*/

//#include "Calculation.h"
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "FileReader.h"

#include <iostream>
#include <unistd.h>

using namespace std;

/**
 * references to particle list in MolSim.cpp
 */
extern std::list<Particle> particles;

class Plotter
{

	public:
		/**
		 * build a file, which stores all the relevant data, for any kind of serialization or visualisation
		 */
		virtual void plotParticles(int iteration, int amountOfParticles){};
};

/**
 * generates .vtu output files, which can be read and displayed by paraview
 */
class VTK : public Plotter
{
	public:
		void plotParticles(int iteration, int amountOfParticles) {
			outputWriter::VTKWriter writer;
			writer.initializeOutput(amountOfParticles);
			
			list<Particle>::iterator iterator;
			iterator = particles.begin();
			int i = 0;
			while (iterator != particles.end()) {
				Particle& p1 = *iterator;
				writer.plotParticle(p1);
				++iterator;
				i++;
				//cout << "P" << i << ": " << p1.toString() << endl;
			}
			writer.writeFile("vtk", iteration);
		}
};
