/**
 * @file rarerare.h
 * @brief Contains rare-rare riemann problems
*/

#ifndef SCENARIOS_RARERARE_H_
#define SCENARIOS_RARERARE_H_

#include "../types.hpp"

namespace scenarios
{

	class RareRare
	{

	private:

		/** Number of cells */
		const unsigned int m_size;
		/** Point of collision (here: in the middle) */
		const unsigned int m_xdis = m_size/2;
		/** initial water height at all cells */
		const signed int m_height = 10;
		/** initial water speed left of xdis */
		const signed int m_leftSpeed = -10;
		/** initial water speed right of xdis */
		const signed int m_rightSpeed = 10;

	public:

		RareRare(unsigned int size)
			: m_size(size)
		{
		}

		/**
		 * @return Initial water height at pos
		 */
		unsigned int getHeight(unsigned int pos)
		{
			return m_height;
		}

		/**
		 * @return Initial water speed at pos
		 */
		signed int getSpeed(unsigned int pos)
		{
			if (pos <= m_xdis)
				return m_leftSpeed;

			return m_rightSpeed; // switch left and right 10 for shock-shock
		}

		/**
		 * @return Cell size of one cell (= domain size/number of cells)
		 */
		T getCellSize()
		{
			return 1000.f / m_size;
		}

	};

}

#endif /* SCENARIOS_RaraRare_H_ */
