#pragma once

#include "InterprocessCopyTool.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "InterprocessBuffer.h"
#include "ILogger.h"
#include <memory>

class InterprocessCopyToolFactory 
{
public:
    InterprocessCopyToolFactory(const std::string& sharedMemoryName, std::shared_ptr<ILogger> logger)
        : sharedMemoryName(sharedMemoryName), logger(logger) {}

    std::unique_ptr<InterprocessCopyTool> createCopyTool() {
        return std::make_unique<InterprocessCopyTool>(
            std::make_unique<FileReader>(),
            std::make_unique<FileWriter>(),
            std::make_unique<InterprocessBuffer>(sharedMemoryName),
            logger);
    }

private:
    std::string sharedMemoryName;
    std::shared_ptr<ILogger> logger;
};
