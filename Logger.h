#pragma once

#include "ILogger.h"
#include <fstream>
#include <string>

class Logger : public ILogger {
public:
    Logger(const std::string& filename);
    ~Logger() override;

    void log(const std::string& message) override;

private:
    std::ofstream logFile;
};




