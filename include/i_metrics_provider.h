#ifndef SYSGUARD_I_METRICS_PROVIDER_H // prevent multiple includes
#define SYSGUARD_I_METRICS_PROVIDER_H
/******************************************************************************
 * Include Files
 ******************************************************************************/
#include "metric_snapshot.h"

/******************************************************************************
 * Class IMetricsProvider
 ******************************************************************************/

class IMetricsProvider
{
  public:
    virtual ~IMetricsProvider() = default;

    virtual MetricSnapshot collect() = 0;
};

#endif
/*---- END OF FILE -----------------------------------------------------------*/