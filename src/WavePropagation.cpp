/**
 * @file WavePropagation.cpp
 * @brief Implementation of WavePropagation
 */

#include "WavePropagation.hpp"


T WavePropagation::computeNumericalFluxes()
{
	float maxWaveSpeed = 0.f;

	// Loop over all edges
	for (unsigned int i = 1; i < m_size+2; i++) 
	{
		T maxEdgeSpeed;

		// Compute net updates
		m_solver.computeNetUpdates(m_h[i-1], m_h[i],
			m_hu[i-1], m_hu[i],
			m_b[i-1], m_b[i],	// Bathymetry
			m_hNetUpdatesLeft[i-1], m_hNetUpdatesRight[i-1],
			m_huNetUpdatesLeft[i-1], m_huNetUpdatesRight[i-1],
			maxEdgeSpeed);

		// Update maxWaveSpeed
		if (maxEdgeSpeed > maxWaveSpeed) maxWaveSpeed = maxEdgeSpeed;
	}

	// Compute CFL condition
	T maxTimeStep = m_cellSize/maxWaveSpeed * .4f;
	return maxTimeStep;
}

void WavePropagation::updateUnknowns(T dt)
{
	// Loop over all inner cells
	for (unsigned int i = 1; i < m_size+1; i++)
	{
        m_h[i] -=  dt/m_cellSize * (m_hNetUpdatesRight[i-1] + m_hNetUpdatesLeft[i]);
        m_hu[i] -= dt/m_cellSize * (m_huNetUpdatesRight[i-1] + m_huNetUpdatesLeft[i]);
	}
}

void WavePropagation::setOutflowBoundaryConditions()
{
	m_h[0] = m_h[1]; m_h[m_size+1] = m_h[m_size];
	m_hu[0] = m_hu[1]; m_hu[m_size+1] = m_hu[m_size];
}

void WavePropagation::computeFroude()
{
	// Loop over all inner cells
	for (unsigned int i = 1; i < m_size+1; i++)
	{
		m_f[i] = m_solver.computeFroude(m_h[i], m_hu[i]);
	}
}