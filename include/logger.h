#ifndef SYSGUARD_LOGGER_H // prevent multiple includes
#define SYSGUARD_LOGGER_H
/******************************************************************************
 * Include Files
 ******************************************************************************/
#include <string>

/******************************************************************************
 * Definitions, Macros
 ******************************************************************************/
enum class LogLevel
{
    Info,
    Warning,
    Error
};

/******************************************************************************
 * Class Logger
 ******************************************************************************/
class Logger
/**
 * @brief Simple logger for console and optional file output
 */
{
  public:
    Logger(bool log_to_file, const std::string &log_file);

    void log(LogLevel level, const std::string &message);
    void info(const std::string &message);
    void warning(const std::string &message);
    void error(const std::string &message);

  private:
    bool log_to_file_;
    std::string log_file_;
};

#endif
/*---- END OF FILE -----------------------------------------------------------*/