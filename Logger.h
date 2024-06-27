#pragma once

#include <fstream>
#include <string>

class Logger 
{
public:
    Logger(const std::string& logName);
    ~Logger();

    void log(const std::string& message);

private:
    std::string logName;
    std::ofstream logFile;
};



