#include "InterprocessCopyTool.h"
#include <iostream>
#include <stdexcept>

InterprocessCopyTool::InterprocessCopyTool(std::unique_ptr<IReader> reader, std::unique_ptr<IWriter> writer, IBuffer& buffer, ISynchronization& sync, std::shared_ptr<ILogger> logger)
    : reader(std::move(reader)), writer(std::move(writer)), buffer(buffer), sync(sync), logger(logger), isReader(!this->buffer.isDoneReading()) {
    logger->log("InterprocessCopyTool created.");
}

InterprocessCopyTool::~InterprocessCopyTool() {
    logger->log("InterprocessCopyTool destroyed.");
}

void InterprocessCopyTool::copy(const std::string& sourcePath, const std::string& destPath)
{
    try
    {
        if (isReader) 
        {
            reader->open(sourcePath);
            logger->log("File reading and buffer writing mode.");

            while ((bytesRead = reader->read(data, bufferSize)) > 0) 
            {
                // handled inside ConcreteFileReader
            }

            buffer.setDoneReading(true);
            sync.getCondRead().notify_all();
            reader->close();
            logger->log("Reading from file to buffer is complete.");
        }
        else 
        {
            writer->open(destPath);
            logger->log("Recording mode from buffer to file.");


            while ((bytesRead = writer->write(data, bufferSize)) > 0)
            {
                // handled inside ConcreteFileWriter
            }

            sync.getCondWrite().notify_all();
            writer->close();
            logger->log("Writing from the buffer to the file is completed.");
        }
    }
    catch (const std::exception& e)
    {
        logger->log("An exception was thrown: " + std::string(e.what()));
        std::cerr << "An exception: " << e.what() << std::endl;
        throw;
    }
}