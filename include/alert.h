#ifndef SYSGUARD_ALERT_H // prevent multiple includes
#define SYSGUARD_ALERT_H
/******************************************************************************
 * Include Files
 ******************************************************************************/
#include <string>

/******************************************************************************
 * Definitions, Macros
 ******************************************************************************/
enum class AlertSeverity
{
    Info,
    Warning,
    Critical
};

/******************************************************************************
 * typedefs
 ******************************************************************************/
struct Alert
{
    AlertSeverity severity{AlertSeverity::Info};
    std::string metric_name;
    std::string message;
};

#endif
/*---- END OF FILE -----------------------------------------------------------*/