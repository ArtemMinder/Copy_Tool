#include "InterprocessCopyTool.h"
#include "InterprocessBuffer.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "Logger.h"
#include <iostream>
#include <memory>
#include <stdexcept>

int main(int argc, char* argv[]) 
{
    if (argc != 4) 
    {
        std::cerr << "Usage: " << argv[0] << " <sourcePath> <destPath> <sharedMemoryName>" << std::endl;
        return 1;
    }

    const std::string sourcePath = argv[1];
    const std::string destPath = argv[2];
    const std::string sharedMemoryName = argv[3];
    const size_t bufferSize = 65536;

    try 
    {
        std::unique_ptr<IBuffer> buffer = std::make_unique<InterprocessBuffer>(sharedMemoryName, bufferSize);
        std::unique_ptr<IReader> reader = std::make_unique<FileReader>();
        std::unique_ptr<IWriter> writer = std::make_unique<FileWriter>();
        std::shared_ptr<ILogger> logger = std::make_shared<Logger>("copy.log");

        InterprocessCopyTool tool(sharedMemoryName, std::move(buffer), std::move(reader), std::move(writer), logger);
        tool.copy(sourcePath, destPath);

    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
