/*
 * Plotter.h
 * This class represents a strategy pattern, which can switch between the chosen output method.
 *  Created on: 31.10.2013
 *  Author: Paul Karlshöfer, Andreas Schmelz, Friedrich Menhorn
 */
#ifndef PLOTTER_H_
#define PLOTTER_H_

#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "outputWriter/XVFWriter.h"
#include "ParticleContainer.h"
#include "LCDomain.h"

#include <iostream>
#include <unistd.h>

using namespace std;
/**
 * Interface for Plotter
 */
class Plotter
{
	protected:
		ParticleContainer particleContainer;
		LCDomain* lcDomain;

	public:
		virtual ~Plotter() {}
		/**
		 * Abstract Function to plotParticles
		 * @param iteration
		 * @param amountOfParticles
		 */
		virtual void plotParticles(int iteration, int amountOfParticles, const std::string& filename, std::vector<double>& parameters)=0;

		ParticleContainer& getParticleContainer();

		void setParticleContainer(ParticleContainer& particleContainer);

		void setLcDomain(LCDomain* lcDomain);
};

/**
 * Actual implementation of a VTK plotter, derived from Plotter
 */
class VTK : public Plotter{
	public:
		/**
		 * Will iterate through particles and plot them in a vtk File
		 * @param iteration
		 * @param amountOfParticles
		 */
		void plotParticles(int iteration, int amountOfParticles, const std::string& filename, std::vector<double>& parameters);
};

/**
 * Actual implementation of a XVF, derived from Plotter
 */
class XVF : public Plotter{
	public:
		/**
		 * Will iterate through particles and plot them in a .txt File
		 * @param iteration
		 * @param amountOfParticles
		 */
		void plotParticles(int iteration, int amountOfParticles, const std::string& filename, std::vector<double>& parameters);

		/**
		 * Will iterate through particles and plot them in a .txt File
		 * @param iteration
		 * @param amountOfParticles
		 */
		std::vector<Particle*> readParticles(std::vector<double>* parameters, const std::string& filename);
};

#endif /* PLOTTER_H */
