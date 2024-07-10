#pragma once

#include "IReader.h"
#include "IWriter.h"
#include "IBuffer.h"
#include "ILogger.h"
#include <memory>
#include <string>

class InterprocessCopyTool 
{
public:
    InterprocessCopyTool(std::unique_ptr<IReader> reader, std::unique_ptr<IWriter> writer, IBuffer& buffer, std::shared_ptr<ILogger> logger);
    void copy(const std::string& sourcePath, const std::string& destPath);
    ~InterprocessCopyTool();

private:
    std::unique_ptr<IReader> reader;
    std::unique_ptr<IWriter> writer;
    IBuffer& buffer;
    std::shared_ptr<ILogger> logger;
    bool isReader;
    static const size_t bufferSize = 1024;
    char data[bufferSize];
    size_t bytesRead;
};



