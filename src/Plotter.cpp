#include "Plotter.h"
#include "ParticleContainer.h"
ParticleContainer& Plotter::getParticleContainer(){
	return particleContainer;
}

void Plotter::setLcDomain(LCDomain& lcDomain) {
	this->lcDomain = lcDomain;
}

void Plotter::setParticleContainer(ParticleContainer& particleContainer) {
	this->particleContainer = particleContainer;
}


void VTK::plotParticles(int iteration, int amountOfParticles) {
	outputWriter::VTKWriter writer;
	writer.initializeOutput(amountOfParticles);

	ParticleContainer** pcArray = lcDomain.getCells();
	int size = lcDomain.getNumberOfCells();

	for(int i = 0; i<size;i++){
		Particle* p;
		while((p = pcArray[i]->nextParticle())!=NULL){
			writer.plotParticle(*p);
		}
	}
	/*
	Particle* p;
	while((p = getParticleContainer().nextParticle()) != NULL) {
		writer.plotParticle(*p);	
	}
	*/
	writer.writeFile("vtk", iteration);

};
