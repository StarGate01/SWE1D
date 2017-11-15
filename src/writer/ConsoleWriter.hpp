/**
 * @file ConsoleWriter.hpp
 * @brief Writes data to an output stream
 */

#ifndef CONSOLEWRITER_H_
#define CONSOLEWRITER_H_

#include <iostream>
#include "../types.hpp"

/**
 * @brief A Collection of different data writers
 */
namespace writer
{

	/**
	 * @brief A simple writer class, that writes data to stdout (or another ostream)
	 */
	class ConsoleWriter
	{
		
		private:

			/** @brief The output stream */
			std::ostream &m_ostream;

		public:

			/**
			 * @brief Constructor
			 * 
			 * @param ostream The output stream
			 */
			ConsoleWriter(std::ostream &ostream = std::cout)
				: m_ostream(ostream)
			{
			}

			/**
			 * @brief Writes all values (without boundary values) to the ostream
			 *
			 * @param h Water height
			 * @param hu Water flux
			 * @param size Number of cells (without boundary values)
			 */
			void write(const T *h, const T *hu, unsigned int size)
			{
				for (unsigned int i=1; i < size+1; i++)  m_ostream << h[i] << ' ';
				m_ostream << '\n';	// do not flush the buffer here (do not use std::endl)
				for (unsigned int i=1; i < size+1; i++)  m_ostream << hu[i] << ' ';
				m_ostream << std::endl;
			}
			
	};

}

#endif /* CONSOLEWRITER_H_ */
