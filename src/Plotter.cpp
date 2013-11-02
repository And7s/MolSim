#include "Plotter.h"

ParticleContainer& Plotter::getParticleContainer(){
	return particleContainer;
}

void Plotter::setParticleContainer(ParticleContainer& particleContainer) {
	this->particleContainer = particleContainer;
}


void VTK::plotParticles(int iteration, int amountOfParticles) {
				outputWriter::VTKWriter writer;
				writer.initializeOutput(amountOfParticles);

				getParticleContainer().resetIterator();

				int i = 0;
				while (!getParticleContainer().isFinished(0)) {
					Particle& p1 = *getParticleContainer().getActParticle();
					writer.plotParticle(p1);
					getParticleContainer().nextParticle(getParticleContainer().getActParticle());
					i++;
					//cout << "P" << i << ": " << p1.toString() << endl;
				}
				writer.writeFile("vtk", iteration);
};
