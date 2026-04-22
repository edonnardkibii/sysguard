/******************************************************************************
* Include Files
******************************************************************************/
#include "config.h"
#include "monitor_engine.h"

#include <cassert>
#include <iostream>

/******************************************************************************
* Code
******************************************************************************/
void test_no_alerts()
/**
* @brief Test that no alerts are generated when values are below thresholds
*/
{
    MonitorEngine engine;
    AppConfig     config;

    MetricSnapshot snapshot;
    snapshot.cpu_usage_percent    = 50.0;
    snapshot.memory_usage_percent = 50.0;
    snapshot.disk_usage_percent   = 50.0;

    auto alerts = engine.evaluate(snapshot, config);
    assert(alerts.empty());
}

//-----------------------------------------------------------------------------

void test_threshold_exceeded()
/**
* @brief Test that alerts are generated when thresholds are exceeded 
*/
{
    MonitorEngine engine;
    AppConfig     config;

    MetricSnapshot snapshot;
    snapshot.cpu_usage_percent    = 90.0;
    snapshot.memory_usage_percent = 90.0;
    snapshot.disk_usage_percent   = 90.0;

    auto alerts = engine.evaluate(snapshot, config);
    assert(!alerts.empty());

}

//-----------------------------------------------------------------------------
int main()
/**
* @brief Entry point for tests
*/
{
    test_no_alerts();
    test_threshold_exceeded();

    std::cout << "All tests passed." << std::endl;

    return 0;
}

/*---- END OF FILE -----------------------------------------------------------*/