#ifndef SYSGUARD_METRIC_SNAPSHOT_H              // prevent multiple includes
#define SYSGUARD_METRIC_SNAPSHOT_H
/******************************************************************************
* Include Files
******************************************************************************/

/******************************************************************************
* typedefs
******************************************************************************/
struct MetricSnapshot
{
    double cpu_usage_percentage{0.0};
    double memory_usage_percentage{0.0};
    double disk_usage_percentage{0.0};
};

#endif
/*---- END OF FILE -----------------------------------------------------------*/