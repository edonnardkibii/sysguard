#ifndef SYSGUARD_MOCK_METRICS_PROVIDER_H       // prevent multiple includes
#define SYSGUARD_MOCK_METRICS_PROVIDER_H
/******************************************************************************
* Include Files
******************************************************************************/
#include "i_metrics_provider.h"

/******************************************************************************
* Class MockMetricsProvider
******************************************************************************/

class MockMetricsProvider : public IMetricsProvider
/**
* @brief Mock metrics provider for deterministic testing
*/
{
    public:

        MetricSnapshot snapshot;

        MetricSnapshot collect() override
        {
            return snapshot;
        }
};

#endif
/*---- END OF FILE -----------------------------------------------------------*/