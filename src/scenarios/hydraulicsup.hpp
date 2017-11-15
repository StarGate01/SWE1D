/**
 * @file hydraulicsup.hpp
 * @brief Hydraulic supercritical scenario
 */

#ifndef SCENARIOS_HYDRAULICSUP_H_
#define SCENARIOS_HYDRAULICSUP_H_

#include "../types.hpp"

namespace scenarios
{

	/**
	 * @brief Implementation of the hydraulic supercritical scenario
	 */
	class HydraulicSup
	{

	private:
		
		/** @brief Number of cells */
		const unsigned int m_size;
		/** @brief Point of collision (here: in the middle) */
		const unsigned int m_xdis = m_size/2;
		/** @brief Initial water height at all cells */
		const signed int m_height = 10;
		/** @brief Initial water speed left of xdis */
		const signed int m_leftSpeed = 50;
		/** @brief Initial water speed right of xdis */
		const signed int m_rightSpeed = -10;

	public:

		/** 
		 * @brief Constructor
		 * 
		 * @param size The size of the domain
		 */
		HydraulicSup(unsigned int size)
			: m_size(size)
		{
		}

		/**
		 * @brief Generates the water height
		 * 
		 * @param pos The cell position
		 * 
		 * @return The initial water height above the bathymetry
		 */
		T getHeight(unsigned int pos)
		{
			return (pos >= 0 && pos <=25) ? -(getBathy(pos)) : 0;
		}

		/**
		 * @brief Generates the water speed
		 * 
		 * @param pos The cell position
		 * 
		 * @return The initial water speed
		 */
		T getSpeed(unsigned int pos)
		{
			return (pos >= 0 && pos <=25) ? 0.18 : 0;
		}

		/**
		 * @brief Generates the bathymetry
		 * 
		 * @param pos The cell position
		 * 
		 * @return The initial bathymetry
		 */
		T getBathy(unsigned int pos)
		{
			if(pos > 8 && pos < 12) return -0.13 - (0.05 * ((pos-10) * (pos-10)));
			return -0.33;
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

#endif /* SCENARIOS_HYDRAULICSUP_H_ */
