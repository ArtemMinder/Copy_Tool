#include <iostream>
#include <memory>
#include <string>
#include "InterprocessCopyToolFactory.h"
#include "ConsoleLogger.h"

int main(int argc, char* argv[]) 
{
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <source> <destination> <shared_memory_name>" << std::endl;
        return 1;
    }

    std::string sourcePath = argv[1];
    std::string destPath = argv[2];
    std::string sharedMemoryName = argv[3];

    auto logger = std::make_shared<ConsoleLogger>();
    logger->log("Programm started.");

    InterprocessCopyToolFactory factory(sharedMemoryName, logger);
    auto copyTool = factory.createCopyTool();

    try 
    {
        copyTool->copy(sourcePath, destPath);
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Exception caught in main: " << ex.what() << std::endl;
        return 1;
    }

    logger->log("Progremm finished.");
    return 0;
}