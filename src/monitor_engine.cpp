/******************************************************************************
 * Include Files
 ******************************************************************************/
#include "monitor_engine.h"

#include <string.h>
#include <string>
#include <vector>

/******************************************************************************
 * Code
 ******************************************************************************/
std::vector<std::string> MonitorEngine::evaluate(const MetricSnapshot &snapshot,
                                                 const AppConfig &config) const
/**
 * @brief Evaluate a metric snapshot against thresholds
 *
 * @param snapshot Current system metrics
 * @param config Application configuration
 * @return List of alert messages
 */
{
    std::vector<std::string> alerts;

    if (snapshot.cpu_usage_percent > config.thresholds.cpu_usage_percent)
    {
        alerts.emplace_back("CPU usage exceeded threshold");
    }

    if (snapshot.memory_usage_percent > config.thresholds.memory_usage_percent)
    {
        alerts.emplace_back("Memory usage exceeded threshold");
    }

    if (snapshot.disk_usage_percent > config.thresholds.disk_usage_percent)
    {
        alerts.emplace_back("Disk usage exceeded threshold");
    }

    return alerts;
}

/*---- END OF FILE -----------------------------------------------------------*/