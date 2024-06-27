#include "Logger.h"

Logger::Logger(const std::string& logName)
    : logName(logName) {
    logFile.open(logName, std::ios::app);
    if (!logFile.is_open()) 
    {
        throw std::runtime_error("Failed to open log file: " + logName);
    }
}

Logger::~Logger() 
{
    if (logFile.is_open()) 
    {
        logFile.close();
    }
}

void Logger::log(const std::string& message) 
{
    logFile << message << std::endl;
}
