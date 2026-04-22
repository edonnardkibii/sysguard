#ifndef SYSGUARD_LINUX_METRICS_PROVIDER_H // prevent multiple includes
#define SYSGUARD_LINUX_METRICS_PROVIDER_H
/******************************************************************************
 * Include Files
 ******************************************************************************/
#include "i_metrics_provider.h"

/******************************************************************************
 * Class IMetricsProvider
 ******************************************************************************/

class LinuxMetricsProvider : public IMetricsProvider
/**
 * @brief Linux implementation of system metrics collection
 */
{
  public:
    MetricSnapshot collect() override;
};

#endif
/*---- END OF FILE -----------------------------------------------------------*/