/**
 * @file bathtub.hpp
 * @brief Bathtub scenario
 */

#ifndef SCENARIOS_BATHTUB_H_
#define SCENARIOS_BATHTUB_H_

#include <cmath>
#include "../types.hpp"

namespace scenarios
{

	/**
	 * @brief Implementation of the Bathtub scenario
	 */
	class Bathtub
	{

	private:
		
		/** @brief Number of cells */
		const unsigned int m_size;
		/** @brief Point of collision (here: in the middle) */
		const unsigned int m_xdis = m_size/2;
	
	public:

		/** 
		 * @brief Constructor
		 * 
		 * @param size The size of the domain
		 */
		Bathtub(unsigned int size) //, std::vector<int> options)
			: m_size(size) //, m_options(options)
		{
		}

		/**
		 * @brief Generates the water height
		 * 
		 * @param pos The cell position
		 * 
		 * @return The initial water height above the bathymetry
		 */
		float getHeight(unsigned int pos)
		{
			if (std::abs(pos - m_size/2) < 15) return 20;
			if(pos <= 5 || (m_size - pos) < 5) return 0;
			return 10;
		}

		/**
		 * @brief Generates the water speed
		 * 
		 * @param pos The cell position
		 * 
		 * @return The initial water speed
		 */
		float getSpeed(unsigned int pos)
		{
		    return 0;
		}

		/**
		 * @brief Generates the bathymetry
		 * 
		 * @param pos The cell position
		 * 
		 * @return The initial bathymetry
		 */
		float getBathy(unsigned int pos)
		{
			if (std::abs(pos - m_size/2) < 30) return -30;
			if(pos <= 5 || (m_size - pos) < 5) return 30;
			return 0;
		}

		/**
		 * @brief Computes the cell size
		 * 
		 * Calculates domain size / number of cells
		 * 
		 * @return Cell size of one cell
		 */
		T getCellSize()
		{
			return 1000.f / m_size;
		}

	};

}

#endif /* SCENARIOS_BATHTUB_H_ */
