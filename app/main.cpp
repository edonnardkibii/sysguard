/******************************************************************************
* Include Files
******************************************************************************/

#include "config.h"
#include "linux_metrics_provider.h"
#include "monitor_engine.h"

//#include <exception>
#include <iostream>

/******************************************************************************
* Code
******************************************************************************/

int main()
{
    try 
    {
        const AppConfig config{load_config("config/example_config.ini")};

        LinuxMetricsProvider provider;
        MetricSnapshot snapshot = provider.collect();

        MonitorEngine engine;
        const auto alerts = engine.evaluate(snapshot, config);

        std::cout << "sysguard starting..." << std::endl;

        for(const auto& alert : alerts)
        {
            std::cout << "[WARNING] " << alert << std::endl; 
        }

        std::cout << "sysguard safely ended" << std::endl;

        return 0;
    
    } 
    catch (const std::exception& exception) 
    {
        std::cerr << "Failed to start sysguard" << exception.what() << std::endl;
        return 1;
    }
}

/*---- END OF FILE -----------------------------------------------------------*/