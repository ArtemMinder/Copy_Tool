#include "FileReader.h"
#include "FileWriter.h"
#include "InterprocessBuffer.h"
#include "InterprocessCopyTool.h"
#include "ConsoleLogger.h"
#include <memory>

int main() {
    std::string sourcePath = "source.txt";
    std::string destPath = "target.txt";
    std::string sharedMemoryName = "shared_memory";

    std::shared_ptr<ILogger> logger = std::make_shared<ConsoleLogger>();
    std::unique_ptr<IReader> reader = std::make_unique<FileReader>();
    std::unique_ptr<IWriter> writer = std::make_unique<FileWriter>();
    std::unique_ptr<IBuffer> buffer = std::make_unique<InterprocessBuffer>(sharedMemoryName);

    InterprocessCopyTool copyTool(std::move(reader), std::move(writer), std::move(buffer), logger);

    try {
        copyTool.copy(sourcePath, destPath);
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception caught in main: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
