/**
 * @brief  Implementation of the Logger class
 * @author Akila Halawatha
 */

#include "Logger.h"
#include <iostream>

using namespace std;

LogLevel Logger::msLogLevel;

/**
 * @brief Static function to set the log level
 * @param[in]  logLevel                 Log level to be set
 *
 * @return None
 */
void Logger::setLogLevel(LogLevel logLevel)
{
    msLogLevel = logLevel;
}

/**
 * @brief Static function to perform the logging
 * @param[in]  logLevel                 Log level of the logging data
 * @param[in]  logData                  Data to log
 *
 * @return Logging was successful
 */
bool Logger::log(LogLevel loglevel, string logData)
{
    bool ret = false;
    string prefix = "";

    do
    {
        if(loglevel > msLogLevel)
        {
            ret = true;
            break;
        }

        switch(loglevel)
        {
            case ERROR:
                prefix = "[E]: ";
                break;
            case WARN:
                prefix = "[W]: ";
                break;
            case INFO:
                prefix = "[I]: ";
                break;
            case DEBUG:
                prefix = "[D]: ";
                break;
            default:
                prefix = "";
                break;
        }

        cout << prefix << logData << endl;
        ret = true;

	} while (false);

    return ret;
}
