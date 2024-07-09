#include "InterprocessCopyTool.h"
#include <iostream>
#include <stdexcept>

InterprocessCopyTool::InterprocessCopyTool(std::unique_ptr<IReader> reader, 
    std::unique_ptr<IWriter> writer,
    std::unique_ptr<IBuffer> buffer,
    std::shared_ptr<ILogger> logger)
    : reader(std::move(reader)),
    writer(std::move(writer)),
    buffer(std::move(buffer)), 
    logger(logger), 
    isReader(!this->buffer->isDoneReading()) 
{
    logger->log("InterprocessCopyTool created.");
}

InterprocessCopyTool::~InterprocessCopyTool()
{
    logger->log("InterprocessCopyTool destroyed.");
}

void InterprocessCopyTool::copy(const std::string& sourcePath, const std::string& destPath) {
    try {
        if (isReader) {
            logger->log("File reading and buffer writing mode.");

            reader->open(sourcePath);

            constexpr size_t bufferSize = 1024;
            char data[bufferSize];
            size_t bytesRead;

            do {
                bytesRead = reader->read(data, sizeof(data));
                if (bytesRead > 0) {
                    buffer->write(data, bytesRead);
                }
            } while (bytesRead > 0);

            reader->close();
            buffer->setDoneReading(true);

            isReader = false;
            logger->log("Reading from file to buffer is complete.");
        }
        else {
            logger->log("Recording mode from buffer to file.");

            writer->open(destPath);

            constexpr size_t bufferSize = 1024;
            char data[bufferSize];
            size_t bytesRead;

            do {
                bytesRead = buffer->read(data, sizeof(data));
                if (bytesRead > 0) {
                    writer->write(data, bytesRead);
                }
            } while (bytesRead > 0);

            writer->close();
            buffer->setDoneReading(false);

            logger->log("Writing from the buffer to the file is completed.");
        }
    }
    catch (const std::exception& e) {
        logger->log("An exception was thrown: " + std::string(e.what()));
        std::cerr << "An exception: " << e.what() << std::endl;
        throw;
    }
}





