/**
 * @file main.cpp
 * @brief Framwork entry point
 */

#include <cstring>
#include "types.hpp"
#include "WavePropagation.hpp"
#include "writer/VtkWriter.hpp"
#include "tools/args.hpp"

#include "scenarios/hydraulicsup.hpp"
#include "scenarios/hydraulicsub.hpp"
#include "scenarios/dambreak.hpp"
#include "scenarios/shockshock.hpp"
#include "scenarios/rarerare.hpp"
#include "scenarios/bathtub.hpp"
// #include "writer/ConsoleWriter.h"

/**
 * @brief OS entry point
 * 
 * @param argc Argument count
 * @param argv Argument buffer
 * 
 * @return The error code
 */
int main(int argc, char** argv)
{
	// Parse command line parameters
	tools::Args args(argc, argv);

	// Scenario
	scenarios::Bathtub scenario(args.size()); //, args.options());

	// Allocate memory
	// Water height
	T *h = new T[args.size()+2];
	// Momentum
	T *hu = new T[args.size()+2];
	//Bathymetry 0 is sealevel
	T *b = new T[args.size()+2];
	//Frode numbers
	T *f = new T[args.size()+2];

	// Initialize water height and momentum
	for (unsigned int i = 0; i < args.size()+2; i++)
	{
		b[i] = scenario.getBathy(i);
		h[i] = scenario.getHeight(i) - b[i]; //substract bathymetry, b/c water height is given as surface level, not water volume
		if (h[i] < ZERO_PRECISION) {
			h[i] = 0;
		}
		hu[i] = scenario.getSpeed(i);
		f[i] = 0;
	}

	// Create a writer that is responsible printing out values
	//writer::ConsoleWriter writer;
	writer::VtkWriter writer("swe1d", scenario.getCellSize());

	// Helper class computing the wave propagation
	WavePropagation wavePropagation(args.size(), scenario.getCellSize(), h, hu, b, f);
	//Calculate initial froude numbers
	wavePropagation.computeFroude();
	// Write initial data
	tools::Logger::logger.info("Initial data");

	// Current time of simulation
	T t = 0;
	writer.write(t, h, hu, b, f, args.size());

	for (unsigned int i = 0; i < args.timeSteps(); i++) 
	{
		// Do one time step
		tools::Logger::logger << "Computing timestep " << i << " at time " << t << std::endl;
		// Update boundaries
		wavePropagation.setOutflowBoundaryConditions();
		// Compute numerical flux on each edge (and frode numbers)
		T maxTimeStep = wavePropagation.computeNumericalFluxes();
		// Update unknowns from net updates
		wavePropagation.updateUnknowns(maxTimeStep);
		//Update froude numbers
		wavePropagation.computeFroude();
		// Update time
		t += maxTimeStep;
		// Write new values
		writer.write(t, h, hu, b, f, args.size());
	}

	// Free allocated memory
	delete [] h;
	delete [] hu;
	delete [] b;
	delete [] f;

	return 0;
}
