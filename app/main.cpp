/******************************************************************************
* Include Files
******************************************************************************/

#include "config.h"

#include <exception>
#include <iostream>

/******************************************************************************
* Code
******************************************************************************/

int main()
{
    try 
    {
        const AppConfig config{load_config("config/example_config.ini")};

        std::cout << "sysguard starting..." << std::endl;

        std::cout << "CPU threshold: " 
                  << config.thresholds.cpu_usage_percent 
                  << std::endl;
        std::cout << "Memory threshold: " 
                  << config.thresholds.memory_usage_percent 
                  << std::endl;
        std::cout << "Disk threshold: " 
                  << config.thresholds.disk_usage_percent
                  << std::endl;
    
    } 
    catch (const std::exception& exception) 
    {
        std::cerr << "Failed to start sysguard" << exception.what() << std::endl;
        return 1;
    }
}

/*---- END OF FILE -----------------------------------------------------------*/