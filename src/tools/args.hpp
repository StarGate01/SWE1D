/**
 * @file args.hpp
 * @brief Command line parser
 */

#ifndef TOOLS_ARGS_H_
#define TOOLS_ARGS_H_

#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include "logger.hpp"

/**
 * @brief Collection of miscellaneous helpers
 */
namespace tools
{

	/**
	 * @brief Parse command line arguments
	 */
	class Args
	{

	private:

		/** @brief Domain size */
		unsigned int m_size;

		/** @brief Number of time steps we want to simulate */
		unsigned int m_timeSteps;

		/** @brief Array of extra option for the scenario */
		// std::vector<int> m_options;

	public:

		/**
		 * @brief Constructor
		 * 
		 * @param argc Argument buffer length
		 * @param argv Argument buffer
		 */
		Args(int argc, char** argv)
			: m_size(100), m_timeSteps(500.0)
		{
			const struct option longOptions[] = {
				{"size", required_argument, 0, 's'},
				{"time", required_argument, 0, 't'},
				//{"options", optional_argument, 0, 'o'},
				{"help", no_argument, 0, 'h'},
				{0, 0, 0, 0}
			};

			int c;
			int optionIndex = 0;
			int parseIndex = 0;
			std::istringstream ss;
			while ((c = getopt_long(argc, argv, "s:t:h", longOptions, &optionIndex)) >= 0) //"s:t:o:h"
			{
				switch (c) 
				{
				case 0:
					tools::Logger::logger.error("Could not parse command line arguments");
					break;
				case 's':
					ss.clear();
					ss.str(optarg);
					ss >> m_size;
					std::cout << m_size << std::endl;
					break;
				case 't':
					ss.clear();
					ss.str(optarg);
					ss >> m_timeSteps;
					std::cout << m_timeSteps << std::endl;
					break;
				/*case 'o':
					parseIndex = optionIndex - 1;
					while(parseIndex < argc) {
						std::string next = argv[parseIndex];
						parseIndex++;
						if(next.at(0) != '-')
						{
							ss.clear();
							ss.str(next);
							int optionval = 0;
							ss >> optionval;
							m_options.push_back(optionval);
							std::cout << "Got option: " << optionval << std::endl;
						}
						else break;
					}
					optionIndex = parseIndex - 1;
					break;*/
				case 'h':
					printHelpMessage();
					exit(0);
					break;
				case '?':
					printHelpMessage(std::cerr);
					abort();
					break;
				default:
					tools::Logger::logger.error("Could not parse command line arguments");
					break;
				}
			}
		}

		/**
		 * @brief The domain size
		 */
		unsigned int size()
		{
			return m_size;
		}

		/**
		 * @brief The number of time steps
		 */
		unsigned int timeSteps()
		{
			return m_timeSteps;
		}

		/* std::vector<int> options()
		{
			return m_options;
		} */

	private:

		/**
		 * @brief Prints the help message, showing all available options
		 *
		 * @param[out] out The output stream the should be used for printing
		 */
		void printHelpMessage(std::ostream &out = std::cout)
		{
			out << "Usage: SWE1D [OPTIONS...]" << std::endl
				<< "  -s, --size=SIZE              domain size" << std::endl
				<< "  -t, --time=TIME              number of simulated time steps" << std::endl
				//<< "  -o, --options=OP1 OP2 ...    optional arguments for the scenario" << std::endl
				<< "  -h, --help                   this help message" << std::endl;
		}
		
	};

}

#endif /* TOOLS_ARGS_H_ */
