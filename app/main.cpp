/******************************************************************************
 * Include Files
 ******************************************************************************/

#include "config.h"
#include "linux_metrics_provider.h"
#include "logger.h"
#include "monitor_engine.h"

#include <exception>
#include <iostream>

/******************************************************************************
 * Code
 ******************************************************************************/

int main()
{
    try
    {
        const AppConfig config{load_config("../config/example_config.ini")};
        Logger logger{config.logging.log_to_file, config.logging.log_file};

        logger.info("sysguard starting");

        LinuxMetricsProvider provider;
        const MetricSnapshot snapshot{provider.collect()};

        MonitorEngine engine;
        const auto alerts{engine.evaluate(snapshot, config)};

        for (const auto &alert : alerts)
        {
            logger.warning(alert);
        }

        if (alerts.empty())
        {
            logger.info("No theshold violations detected");
        }

        return 0;
    }
    catch (const std::exception &exception)
    {
        Logger logger{false, ""};
        logger.error(exception.what());
        return 1;
    }
}

/*---- END OF FILE -----------------------------------------------------------*/