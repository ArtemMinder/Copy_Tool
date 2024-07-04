#pragma once

#include "IBuffer.h"
#include "IReader.h"
#include "IWriter.h"
#include "ILogger.h"
#include <memory>

class InterprocessCopyTool {
public:
    InterprocessCopyTool(const std::string& sharedMemoryName, 
        std::unique_ptr<IBuffer> buffer, 
        std::unique_ptr<IReader> reader,
        std::unique_ptr<IWriter> writer,
        std::shared_ptr<ILogger> logger);
    ~InterprocessCopyTool();

    void copy(const std::string& sourcePath, const std::string& destPath);

private:
    std::string sharedMemoryName;
    std::unique_ptr<IBuffer> buffer;
    std::unique_ptr<IReader> reader;
    std::unique_ptr<IWriter> writer; 
    std::shared_ptr<ILogger> logger;
};