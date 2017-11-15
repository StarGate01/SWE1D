/**
 * @file WavePropagation.hpp
 * @brief Implements an adapter to a wave solver
 */

#ifndef WAVEPROPAGATION_H_
#define WAVEPROPAGATION_H_

#include "types.hpp"

/**
 * @brief Supresses the solvers debug output
 */
#define SUPPRESS_SOLVER_DEBUG_OUTPUT

// Include the solver that is currently used
//#include "../submodules/solvers_preset/src/solver/FWave.hpp"
#include "../submodules/solvers/src/solver/FWave.hpp"

/**
 * @brief The solver adapter and framwork
 * 
 * Allocated variables:
 *   unknowns h,hu are defined on grid indices [0,..,n+1] (done by the caller)
 *     -> computational domain is [1,..,nx]
 *     -> plus ghost cell layer
 *
 *   net-updates are defined for edges with indices [0,..,n]
 *
 * A left/right net update with index (i-1) is located on the edge between
 *   cells with index (i-1) and (i):
 * <pre>
 *   *********************
 *   *         *         *
 *   *  (i-1)  *   (i)   *
 *   *         *         *
 *   *********************
 *
 *             *
 *            ***
 *           *****
 *             *
 *             *
 *    NetUpdatesLeft(i-1)
 *             or
 *    NetUpdatesRight(i-1)
 * </pre>
 */
class WavePropagation
{

	private:

		/** @brief The water heights */
		T *m_h;
		/** @brief The water fluxes */
		T *m_hu;
		/** @brief The bathymetries */
		T *m_b;
		/** @brief The froude numbers */
		T *m_f;

		/** @brief The left going net-updates fot the water height */
		T *m_hNetUpdatesLeft;
		/** @brief The right going net-updates fot the water height */
		T *m_hNetUpdatesRight;
		/** @brief The left going net-updates fot the water flux */
		T *m_huNetUpdatesLeft;
		/** @brief The right going net-updates fot the water flux */
		T *m_huNetUpdatesRight;

		/** @brief The size of the domain */
		unsigned int m_size;
		/** @brief The size of a cell */
		T m_cellSize;

		/** @brief The solver used in WavePropagation::computeNumericalFluxes */
		solver::FWave<T> m_solver;

	public:

		/**
		 * @brief Constructor
		 * 
		 * @param[in] size Domain size (= number of cells) without ghost cells
		 * @param[in] cellSize Size of one cell
		 * @param[out] h The water heights
		 * @param[out] hu The fluxes
		 * @param[in] b The bathymetry
		 * @param[out] f The froude numbers
		 */
		WavePropagation(unsigned int size, T cellSize, T *h, T *hu, T *b, T *f) 
			: m_h(h), m_hu(hu), m_size(size), m_cellSize(cellSize), m_b(b), m_f(f)
		{
			// Allocate net updates
			m_hNetUpdatesLeft = new T[size+1];
			m_hNetUpdatesRight = new T[size+1];
			m_huNetUpdatesLeft = new T[size+1];
			m_huNetUpdatesRight = new T[size+1];
		}

		/**
		 * @brief Destructor
		 */
		~WavePropagation()
		{
			// Free allocated memory
			delete [] m_hNetUpdatesLeft;
			delete [] m_hNetUpdatesRight;
			delete [] m_huNetUpdatesLeft;
			delete [] m_huNetUpdatesRight;
		}

		/**
		 * @brief Computes the net-updates from the unknowns
		 *
		 * @return The maximum possible time step
		 */
		T computeNumericalFluxes();

		/**
		 * @brief Update the unknowns with the already computed net-updates
		 *
		 * @param dt Time step size
		 */
		void updateUnknowns(T dt);

		/**
		 * @brief Updates h and hu according to the outflow condition to both boundaries
		 */
		void setOutflowBoundaryConditions();

		/**
		 * @brief Computes the froude numbers
		 */
		void computeFroude();

};

#endif /* WAVEPROPAGATION_H_ */
