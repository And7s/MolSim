#include "Plotter.h"
#include "ParticleContainer.h"
ParticleContainer& Plotter::getParticleContainer(){
	return particleContainer;
}

void Plotter::setParticleContainer(ParticleContainer& particleContainer) {
	this->particleContainer = particleContainer;
}


void VTK::plotParticles(int iteration, int amountOfParticles) {
	outputWriter::VTKWriter writer;
	writer.initializeOutput(amountOfParticles);

	Particle* p;


	//getParticleContainer().show();
	while((p = getParticleContainer().nextParticle()) != NULL) {
		writer.plotParticle(*p);	
	}
	writer.writeFile("vtk", iteration);

};
