/**
 * @file dambreak.hpp
 * @brief Dam break scenario
 */

#ifndef SCENARIOS_DAMBREAK_H_
#define SCENARIOS_DAMBREAK_H_

// #include <vector>
#include "../types.hpp"

/**
 * @brief Scenarios for the 1D solver
 */ 
namespace scenarios
{

	/**
	 * @brief Implementation of the Dam break scenario
	 */
	class DamBreak
	{

	private:
		
		/** @brief Number of cells */
		const unsigned int m_size;
		/** @brief Point of collision (here: in the middle) */
		const unsigned int m_xdis = m_size/2;
		/** @brief initial water height left of xdis*/
		const float m_leftHeight = 20;
		/** @brief initial water height righr of xdis*/
		const float m_rightHeight = 5;
		/** @brief initial water speed left of xdis */
		const float m_leftSpeed = 0;
		/** @brief initial water speed right of xdis */
		const float m_rightSpeed = 0;

		/** @brief Point of bathymetry change on the left*/
		const unsigned int m_lbdis = 10;
		/** @brief Point of bathymetry change on the left*/
		const unsigned int m_rbdis = 20;
		/** @brief Initial bathymetry left of lbdis */
		const float m_leftB = -5;
		/** @brief Initial bathymetry between lbdis and rbdis */
		const float m_middleB = -30;
		/** @brief Initial bathymetryright right of rbdis */
		const float m_rightB = -10;

		/** @brief Additional options */
		//std::vector<int> m_options;

	public:

		/** 
		 * @brief Constructor
		 * 
		 * @param size The size of the domain
		 */
		DamBreak(unsigned int size) //, std::vector<int> options)
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
			if (pos <= m_size/2) return m_leftHeight;
			return m_rightHeight;
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
			if (pos <= m_xdis) return m_leftSpeed;
			return m_rightSpeed; 
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
			if (pos <= m_lbdis) return m_leftB;
			else if (pos <= m_rbdis) return m_middleB;
			return m_rightB; 
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

#endif /* SCENARIOS_DAMBREAK_H_ */
