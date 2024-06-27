#pragma once

#include "AbstractBuffer.h"
#include "IReader.h"
#include "IWriter.h"
#include "Logger.h"
#include <memory>
#include <string>

class InterprocessCopyTool 
{
public:
    InterprocessCopyTool(const std::string& sharedMemoryName, std::unique_ptr<AbstractBuffer> buffer,
        std::unique_ptr<IReader> reader, std::unique_ptr<IWriter> writer, Logger& logger);
    ~InterprocessCopyTool();

    void copy(const std::string& sourcePath, const std::string& destPath);

private:
    std::string sharedMemoryName;
    std::unique_ptr<AbstractBuffer> buffer;
    std::unique_ptr<IReader> reader;
    std::unique_ptr<IWriter> writer;
    Logger& logger;
};

