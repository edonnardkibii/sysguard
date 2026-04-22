/******************************************************************************
 * Include Files
 ******************************************************************************/
#include "logger.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

/******************************************************************************
 * Code
 ******************************************************************************/
namespace
{
std::string to_string(const LogLevel level)
/**
 * @brief Convert a log level to text
 *
 * @param level Log severity.
 * @return Text representation of the log level.
 */
{
    switch (level)
    {
    case LogLevel::Info:
        return "INFO";
    case LogLevel::Warning:
        return "WARN";
    case LogLevel::Error:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}
} // namespace

//-----------------------------------------------------------------------------

Logger::Logger(const bool log_to_file, const std::string &log_file)
    : log_to_file_(log_to_file), log_file_(log_file)
/**
 *@brief Create a logger instance.
 *
 *@param log_to_file Enable file logging when true.
 *@param log_file Path to the log file
 */
{
}

//-----------------------------------------------------------------------------

void Logger::log(const LogLevel level, const std::string &message)
/**
 *@brief Log a message with the specified severity.
 *
 *@param level Log severity.
 *@param message Message text.
 */
{
    const std::string formatted_message{"[" + to_string(level) + "] " +
                                        message};

    std::cout << formatted_message << std::endl;

    if (log_to_file_)
    {
        std::ofstream file{log_file_, std::ios::app};

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open log file: " + log_file_);
        }

        file << formatted_message << '\n';
    }
}

//-----------------------------------------------------------------------------

void Logger::info(const std::string &message)
/**
 *@brief Log an informational message
 *
 *@param message Message text.
 */
{
    log(LogLevel::Info, message);
}

//-----------------------------------------------------------------------------

void Logger::warning(const std::string &message)
/**
 *@brief Log a warning message
 *
 *@param message Message text.
 */
{
    log(LogLevel::Warning, message);
}

//-----------------------------------------------------------------------------

void Logger::error(const std::string &message)
/**
 *@brief Log an error message
 *
 *@param message Message text.
 */
{
    log(LogLevel::Error, message);
}

/*---- END OF FILE -----------------------------------------------------------*/