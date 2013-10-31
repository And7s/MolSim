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

extern std::list<Particle> particles;

class Plotter
{

	public:
		virtual void plotParticles(int iteration){};
};

class VTK : public Plotter
{
	public:
		void plotParticles(int iteration) {
			outputWriter::VTKWriter writer;
			writer.initializeOutput(4);
			
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
