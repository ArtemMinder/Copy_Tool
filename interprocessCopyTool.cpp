#include "InterprocessCopyTool.h"
#include <stdexcept>

InterprocessCopyTool::InterprocessCopyTool(const std::string& sharedMemoryName, std::unique_ptr<IBuffer> buffer, 
    std::unique_ptr<IReader> reader, std::unique_ptr<IWriter> writer, std::shared_ptr<ILogger> logger)
    : sharedMemoryName(sharedMemoryName), buffer(std::move(buffer)), reader(std::move(reader)), writer(std::move(writer)),
    logger(std::move(logger)) {}

InterprocessCopyTool::~InterprocessCopyTool() {}

void InterprocessCopyTool::copy(const std::string& sourcePath, const std::string& destPath) 
{
    try 
    {
        reader->open(sourcePath);
        writer->open(destPath);

        char data[4096];
        size_t bytesRead;
        while ((bytesRead = reader->read(data, sizeof(data))) > 0) 
        {
            buffer->write(data, bytesRead);
            size_t bytesWritten;
            while ((bytesWritten = buffer->read(data, sizeof(data))) > 0) 
            {
                writer->write(data, bytesWritten);
            }
            throw std::runtime_error("Simulated error after first memory block operation");
        }

        reader->close();
        writer->close();
    }
    catch (const std::exception& e) 
    {
        logger->log("Exception caught during copy operation: " + std::string(e.what()));
        throw;
    }
}
