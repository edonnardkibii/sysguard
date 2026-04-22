#ifndef SYSGUARD_CONFIG_H // prevent multiple includes
#define SYSGUARD_CONFIG_H
/******************************************************************************
 * Include Files
 ******************************************************************************/
#include <string>

/******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * @brief Threshold configuration for monitored system metrics
 */
struct ThresholdConfig
{
    double cpu_usage_percent{85.0};
    double memory_usage_percent{80.0};
    double disk_usage_percent{90.0};
};

/**
 * @brief Logging configuration for the application
 */
struct LoggingConfig
{
    bool log_to_file{false};
    std::string log_file{"logs/sysguard.log"};
    std::string level{"info"};
};

/**
 * @brief complete application configuration
 */
struct AppConfig
{
    ThresholdConfig thresholds;
    LoggingConfig logging;
};

/******************************************************************************
 * Function Prototypes
 ******************************************************************************/

AppConfig load_config(const std::string &file_path);

#endif
/*---- END OF FILE -----------------------------------------------------------*/