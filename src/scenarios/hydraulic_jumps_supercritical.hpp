/**
 * @file shockschock.h
 * @brief Contains shock-shock riemann problems
*/

#ifndef SCENARIOS_HYDRAULIC_SUPERCRITICAL_H_
#define SCENARIOS_HYDRAULIC_SUPERCRITICAL_H_

#include "../types.hpp"

namespace scenarios
{

	class ShockShock
	{

	private:
		
		/** Number of cells */
		const unsigned int m_size;
		/** Point of collision (here: in the middle) */
		const unsigned int m_xdis = m_size/2;
		/** initial water height at all cells */
		const signed int m_height = 10;
		/** initial water speed left of xdis */
		const signed int m_leftSpeed = 50;
		/** initial water speed right of xdis */
		const signed int m_rightSpeed = -10;

	public:

		ShockShock(unsigned int size)
			: m_size(size)
		{
		}

		//TODO: Add bathymetry

		/**
		 * @return Initial water height at pos
		 */
		unsigned int getHeight(unsigned int pos)
		{
			//TODO: Change to correct height
			return m_height;
		}

		/**
		 * @return Initial water speed at pos
		 */
		signed int getSpeed(unsigned int pos)
		{
			return (pos >= 0 && pos <=25) ? 0.18 : 0;
		}

		/**
		 * @return Cell size of one cell (= domain size/number of cells)
		 */
		T getCellSize()
		{
			return 1000.f / m_size;
		}

		T getBathy(unsigned int pos)
		{
			if(pos > 8 && pos < 12)
				return -0.13-0.05*(pos-10)*(pos-10);
			return -0.33;
		}
	};

}

#endif /* SCENARIOS_ShockShock_H_ */
