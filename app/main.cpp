/******************************************************************************
* Include Files
******************************************************************************/

#include "config.h"
#include "monitor_engine.h"
#include "metric_snapshot.h"

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

        MetricSnapshot snapshot;
        snapshot.cpu_usage_percent = 90.0;
        snapshot.memory_usage_percent = 50.0;
        snapshot.disk_usage_percent = 95.0;

        MonitorEngine engine;
        const auto alerts = engine.evaluate(snapshot, config);

        std::cout << "sysguard starting..." << std::endl;

        for(const auto& alert : alerts)
        {
            std::cout << "[WARNING] " << alert << std::endl; 
        }

        return 0;
    
    } 
    catch (const std::exception& exception) 
    {
        std::cerr << "Failed to start sysguard" << exception.what() << std::endl;
        return 1;
    }
}

/*---- END OF FILE -----------------------------------------------------------*/