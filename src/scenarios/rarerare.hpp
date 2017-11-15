/**
 * @file rarerare.hpp
 * @brief Rare-Rare scenario
*/

#ifndef SCENARIOS_RARERARE_H_
#define SCENARIOS_RARERARE_H_

#include "../types.hpp"

namespace scenarios
{

	/**
	 * @brief Implementation of the Rare-Rare scenario
	 */
	class RareRare
	{

	private:

		/** @brief Number of cells */
		const unsigned int m_size;
		/** @brief Point of collision (here: in the middle) */
		const unsigned int m_xdis = m_size/2;
		/** @brief Initial water height at all cells */
		const signed int m_height = 10;
		/** @brief Initial water speed left of xdis */
		const signed int m_leftSpeed = -10;
		/** @brief Initial water speed right of xdis */
		const signed int m_rightSpeed = 10;

	public:

		/** 
		 * @brief Constructor
		 * 
		 * @param size The size of the domain
		 */
		RareRare(unsigned int size)
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
		unsigned int getHeight(unsigned int pos)
		{
			return m_height;
		}

		/**
		 * @brief Generates the water speed
		 * 
		 * @param pos The cell position
		 * 
		 * @return The initial water speed
		 */
		signed int getSpeed(unsigned int pos)
		{
			if (pos <= m_xdis) return m_leftSpeed;
			return m_rightSpeed; // switch left and right 10 for shock-shock
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

#endif /* SCENARIOS_RARERARE_H_ */
