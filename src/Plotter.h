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
#include "ParticleContainer.h"

#include <iostream>
#include <unistd.h>

using namespace std;
/**
 * Interface for Plotter
 */
class Plotter
{
	private:
		ParticleContainer particleContainer;

	public:
		virtual ~Plotter() {}
		/**
		 * Abstract Function to plotParticles
		 * @param iteration
		 * @param amountOfParticles
		 */
		virtual void plotParticles(int iteration, int amountOfParticles)=0;

		ParticleContainer& getParticleContainer();

		void setParticleContainer(ParticleContainer& particleContainer);
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
		void plotParticles(int iteration, int amountOfParticles);
};

#endif /* PLOTTER_H */
