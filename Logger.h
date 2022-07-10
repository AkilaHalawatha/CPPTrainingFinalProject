#ifndef LOGGER_H
#define LOGGER_H

/**
 * @brief  Definition of the Logging class
 * @author Akila Halawatha
 */

#include <string>

/**
 * @brief Log level enum
 */
enum LogLevel
{
    NONE,
    ERROR,
    WARN,
    INFO,
    DEBUG
};

/**
 * @brief Logger class to be used for logging activities
 */
class Logger
{
public:
    /**
     * @brief Static function to set the log level
     * @param[in]  logLevel                 Log level to be set
     *
     * @return None
     */
    static void setLogLevel(LogLevel logLevel);

    /**
     * @brief Static function to perform the logging
     * @param[in]  logLevel                 Log level
     * @param[in]  logData                  Data to log
     *
     * @return Logging was successful
     */
    static bool log(LogLevel loglevel, std::string logData);
private:
    static LogLevel msLogLevel;

};

#endif // LOGGER_H