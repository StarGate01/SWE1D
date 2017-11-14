/**
 * @file shockschock.h
 * @brief Contains shock-shock riemann problems
*/

#ifndef SCENARIOS_HYDRAULIC_SUBCRITICAL_H_
#define SCENARIOS_HYDRAULIC_SUBCRITICAL_H_

#include "../types.hpp"

namespace scenarios
{

	class HydraulicSub
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
		HydraulicSub(unsigned int size)
			: m_size(size)
		{
		}

		/**
		 * @return Initial water height at pos
		 */
		T getHeight(unsigned int pos)
		{
			return (pos >= 0 && pos <=25) ? -(getBathy(pos)) : 0;
		}

		/**
		 * @return Initial water speed at pos
		 */
		T getSpeed(unsigned int pos)
		{
			return (pos >= 0 && pos <=25) ? 4.42 : 0;
		}

		/**
		 * @return Cell size of one cell (= domain size/number of cells)
		 */
		T getCellSize()
		{
			return 1000.f / m_size;
		}
		
		/**
		 * @return Bathymetrie according to assignment
		*/
		T getBathy(unsigned int pos)
		{
			if(pos > 8 && pos < 12)
				return -1.8-(0.05*((pos-10)*(pos-10)));
			return -2;
		}
	};

}

#endif /* SCENARIOS_ShockShock_H_ */
