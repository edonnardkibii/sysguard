#ifndef SYSGUARD_MONITOR_ENGINE_H              // prevent multiple includes
#define SYSGUARD_MONITOR_ENGINE_H
/******************************************************************************
* Include Files
******************************************************************************/
#include "config.h"
#include "metric_snapshot.h"

#include <string>
#include <vector>

/******************************************************************************
* Class MonitorEngine
******************************************************************************/
class MonitorEngine
{
    public:
        std::vector<std::string> evaluate(const MetricSnapshot& snapshot,
                                          const AppConfig& config) const;
};

#endif
/*---- END OF FILE -----------------------------------------------------------*/