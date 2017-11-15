/**
 * @file logger.hpp
 * @brief Provides logging functionality
 */

#ifndef TOOLS_LOGGER_H_
#define TOOLS_LOGGER_H_

#include <cstdlib>
#include <iostream>

namespace tools 
{

	/**
	 * @brief Logs messages to an output stream
	 */
	class Logger 
	{

		public:

			/** @brief The possible log levels */
			enum Level { INFO, WARNING, ERROR };

		private:

			/** @brief Stream where we print all messages */
			std::ostream* m_output;

		private:

			/**
			 * @brief Constructor
			 */
			Logger() : m_output(&std::cout)
			{
			}

		public:

			/**
			 * @brief Sets the output stream
			 * 
			 * @param output The new output stream
			 */
			void setOutputStream(std::ostream &output)
			{
				m_output = &output;
			}

			/**
			 * @brief Logs a message to the output stream
			 * 
			 * @param message The message
			 * @param level The logging level
			 */
			void log(std::string &message, Level level = INFO)
			{
				log(message.c_str(), level);
			}

			/**
			 * @brief Logs a message to the output stream
			 * 
			 * @param message The message
			 * @param level The logging level
			 */
			void log(const char* message, Level level = INFO)
			{
				switch (level) {
					case INFO:
						info(message);
						break;
					case WARNING:
						warning(message);
						break;
					case ERROR:
						error(message);
						break;
				}
			}

			/**
			 * @brief Logs a message with the info log level
			 * 
			 * @param message The message
			 */
			void info(std::string &message)
			{
				info(message.c_str());
			}

			/**
			 * @brief Logs a message with the info log level
			 * 
			 * @param message The message
			 */
			void info(const char* message)
			{
				*m_output << message << std::endl;
			}

			/**
			 * @brief The stream used for logging info messages
			 * 
			 * @return The unmodified output stream
			 */
			std::ostream& info()
			{
				return *m_output;
			}

			/**
			 * @brief Logs a message with the warning log level
			 * 
			 * @param message The message
			 */
			void warning(std::string &message)
			{
				warning(message.c_str());
			}

			/**
			 * @brief Logs a message with the warning log level
			 * 
			 * @param message The message
			 */
			void warning(const char* message)
			{
				*m_output << "Warning: " << message << std::endl;
			}

			/**
			 * @brief The stream used for logging warning messages
			 * 
			 * @return The output stream with a prepended "Warning: "
			 */
			std::ostream& warning()
			{
				return *m_output << "Warning: ";
			}

			/**
			 * @brief Logs a message with the error log level to stderr
			 * 
			 * @param message The message
			 */
			void error(std::string &message)
			{
				error(message.c_str());
			}

			/**
			 * @brief Logs a message with the error log level to stderr
			 * 
			 * @param message The message
			 */
			void error(const char* message)
			{
				// Error messages are always send to std::cerr
				std::cerr << "Error: " << message << std::endl;
				exit(1);
			}

			/**
			 * @brief Prints arbitrary info messages
			 * 
			 * Can be used to print arbitrary info messages and does not append std::endl.
			 * 
			 * @param value The message to log
			 */
			template<typename T> Logger& operator<<(T value)
			{
				*m_output << value;
				return *this;
			}

			/**
			 * @brief Prints arbitrary info messages
			 * 
			 * Can be used to print arbitrary info messages and allows to print std::endl
			 * 
			 * @param func The output stream callback
			 */
			Logger& operator<<(std::ostream& (*func)(std::ostream&))
			{
				*m_output << func;
				return *this;
			}

		public:
			
			/** @brief Singleton logging instance */
			static Logger logger;

	};

}

#endif /* TOOLS_LOGGER_H_ */
