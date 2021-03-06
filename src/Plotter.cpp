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

	std::vector<Particle*>* particles = lcDomain->getAllParticles();
	Particle* p;

	int num_Particles = particles->size();
	for(int i = 0;i < num_Particles;i++){
		writer.plotParticle(*(*particles)[i]);
	}
	writer.writeFile(filename, iteration);

}
;

void XVF::plotParticles(int iteration, int amountOfParticles, const std::string& filename, std::vector<double>& parameters) {
	outputWriter::XVFWriter writer;
	std::vector<Particle*>* particles = lcDomain->getAllParticles();
	writer.writeFile(*particles, filename, parameters);
}

std::vector<Particle*> XVF::readParticles(std::vector<double>* parameters, const std::string& filename, int* uid) {
	outputWriter::XVFWriter reader;

	std::vector<Particle*> particles;
	particles = reader.readFile(parameters, filename, uid);

	return particles;
}

void CSV::plotParticles(int dimension, int bins, const std::string& filename, std::vector<double>& parameters) {
	outputWriter::CSVWriter writer;
	std::vector<Particle*>* particles = lcDomain->getAllParticles();
	writer.writeFile(*particles);
}
