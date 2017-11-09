/**
 * @file
 *  This file is part of SWE1D
 *
 *  SWE1D is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SWE1D is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SWE1D.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Diese Datei ist Teil von SWE1D.
 *
 *  SWE1D ist Freie Software: Sie koennen es unter den Bedingungen
 *  der GNU General Public License, wie von der Free Software Foundation,
 *  Version 3 der Lizenz oder (nach Ihrer Option) jeder spaeteren
 *  veroeffentlichten Version, weiterverbreiten und/oder modifizieren.
 *
 *  SWE1D wird in der Hoffnung, dass es nuetzlich sein wird, aber
 *  OHNE JEDE GEWAEHELEISTUNG, bereitgestellt; sogar ohne die implizite
 *  Gewaehrleistung der MARKTFAEHIGKEIT oder EIGNUNG FUER EINEN BESTIMMTEN
 *  ZWECK. Siehe die GNU General Public License fuer weitere Details.
 *
 *  Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 *  Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
 * 
 * @copyright 2013 Technische Universitaet Muenchen
 * @author Sebastian Rettenberger <rettenbs@in.tum.de>
 */

#include <cstring>
#include "types.hpp"
#include "WavePropagation.hpp"
#include "writer/VtkWriter.hpp"
#include "tools/args.hpp"

#include "scenarios/dambreak.hpp"
//#include "scenarios/shockshock.hpp"
//#include "scenarios/rarerare.hpp"
//#include "writer/ConsoleWriter.h"

int main(int argc, char** argv)
{
	// Parse command line parameters
	tools::Args args(argc, argv);

	// Scenario
	scenarios::DamBreak scenario(args.size()); //, args.options());

	// Allocate memory
	// Water height
	T *h = new T[args.size()+2];
	// Momentum
	T *hu = new T[args.size()+2];
	//Bathymetry
	T *b = new T[args.size()+2];
	//Bathymetry with offset
	T *b_offset = new T[args.size()+2];
	// Water height (cache)
	T *h_bup = new T[args.size()+2];

	// Initialize water height and momentum
	for (unsigned int i = 0; i < args.size()+2; i++)
	{
		h[i] = scenario.getHeight(i);
		h_bup[i] = scenario.getHeight(i);
		hu[i] = scenario.getSpeed(i);
		b[i] = scenario.getBathy(i);
	}

	// Create a writer that is responsible printing out values
	//writer::ConsoleWriter writer;
	writer::VtkWriter writer("swe1d", scenario.getCellSize());

	// Helper class computing the wave propagation
	WavePropagation wavePropagation(h, hu, args.size(), scenario.getCellSize(), b);

	// Write initial data
	tools::Logger::logger.info("Initial data");

	// Current time of simulation
	T t = 0;
	for (unsigned int i = 0; i < args.size()+2; i++)
	{
		b_offset[i] = b[i] + h_bup[i];
	}
	writer.write(t, h, hu, b_offset, args.size());

	for (unsigned int i = 0; i < args.timeSteps(); i++) 
	{
		// Do one time step
		tools::Logger::logger << "Computing timestep " << i
				<< " at time " << t << std::endl;
		// Update boundaries
		wavePropagation.setOutflowBoundaryConditions();
		// Compute numerical flux on each edge
		T maxTimeStep = wavePropagation.computeNumericalFluxes();
		// Update unknowns from net updates
		wavePropagation.updateUnknowns(maxTimeStep);
		// Update time
		t += maxTimeStep;
		// Write new values
		for (unsigned int i = 0; i < args.size()+2; i++)
		{
			b_offset[i] = b[i] + h_bup[i];
		}
		writer.write(t, h, hu, b_offset, args.size());
	}

	// Free allocated memory
	delete [] h;
	delete [] hu;

	return 0;
}
