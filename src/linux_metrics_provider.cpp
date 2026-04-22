/******************************************************************************
* Include Files
******************************************************************************/
#include "linux_metrics_provider.h"

#include <fstream>
#include <stdexcept>
#include <string>

/******************************************************************************
* Code
******************************************************************************/
static double read_memory_usage_percent()
/**
* @brief Read memory usage from /proc/meminfo
*/
{
    std::ifstream file("/proc/meminfo");

    if(!file.is_open())
    {
        throw std::runtime_error("Failed to read /proc/meminfo");
    }

    std::string key   = "";
    long        value = -1;
    std::string unit  = "";

    long total     = 0;
    long available = 0;

    while(file >> key >> value >> unit)
    {
        if(key == "MemTotal:")
        {
            total = value;
        }
        else if (key == "MemAvailable:")
        {
            available = value;
        }

        if(total && available)
        {
            break;
        }
    }

    if(total == 0)
    {
        throw std::runtime_error("Failed to parse MemTotal");
    }

    return (100.0 * (1.0 - (double)(available) / total));
}

//-----------------------------------------------------------------------------

MetricSnapshot LinuxMetricsProvider::collect()
/**
* @brief collect system metrics from Linux system interfaces
*
* @return Metric snapshot containing CPU, memory and disk usage
*/
{
    MetricSnapshot snapshot{};

    // CPU
    snapshot.cpu_usage_percent    = 0.0;

    // Memory
    snapshot.memory_usage_percent = read_memory_usage_percent();

    // Disk
    snapshot.disk_usage_percent   = 0.0;

    return snapshot;
}

/*---- END OF FILE -----------------------------------------------------------*/