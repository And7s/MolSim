#include "Plotter.h"

ParticleContainer& Plotter::getParticleContainer(){
	return particleContainer;
}

void Plotter::setLcDomain(LCDomain* lcDomain_) {
	lcDomain = lcDomain_;
}

void Plotter::setParticleContainer(ParticleContainer& particleContainer) {
	this->particleContainer = particleContainer;
}


void VTK::plotParticles(int iteration, int amountOfParticles, const std::string& filename, std::vector<double>& parameters) {
	outputWriter::VTKWriter writer;
	writer.initializeOutput(amountOfParticles);

	ParticleContainer** pcArray = lcDomain->getCells();
	int size = lcDomain->getNumberOfCells();

	for(int i = 0; i<size;i++){
		Particle* p;
		while((p = pcArray[i]->nextParticle())!=NULL){
			writer.plotParticle(*p);
		}
	}
	writer.writeFile(filename, iteration);

}
;

void XVF::plotParticles(int iteration, int amountOfParticles, const std::string& filename, std::vector<double>& parameters) {
	outputWriter::XVFWriter writer;

	ParticleContainer** pcArray = lcDomain->getCells();
	int size = lcDomain->getNumberOfCells();
	std::vector<Particle*> particleList;

	for(int i = 0; i<size;i++){
		Particle* p;
		while((p = pcArray[i]->nextParticle())!=NULL){
			particleList.push_back(p);
		}
	}

	writer.writeFile(particleList, filename, parameters);
}

std::vector<Particle*> XVF::readParticles(std::vector<double>* parameters, const std::string& filename) {
	outputWriter::XVFWriter reader;

	std::vector<Particle*> particles;
	particles = reader.readFile(parameters, filename);

	return particles;
}
