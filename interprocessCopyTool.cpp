#include "InterprocessCopyTool.h"
#include <iostream>
#include <stdexcept>

InterprocessCopyTool::InterprocessCopyTool(std::unique_ptr<IReader> reader, std::unique_ptr<IWriter> writer, IBuffer& buffer, std::shared_ptr<ILogger> logger)
    : reader(std::move(reader)), writer(std::move(writer)), buffer(buffer), logger(logger), isReader(!this->buffer.isDoneReading()) {
    logger->log("InterprocessCopyTool создан.");
}

InterprocessCopyTool::~InterprocessCopyTool() {
    logger->log("InterprocessCopyTool уничтожен.");
}

void InterprocessCopyTool::copy(const std::string& sourcePath, const std::string& destPath) {
    try {
        if (isReader) {
            reader->open(sourcePath);
            logger->log("File reading and buffer writing mode.");

            while ((bytesRead = reader->read(data, bufferSize)) > 0) {
                // handled inside ConcreteFileReader
            }

            buffer.setDoneReading(true);
            reader->close();
            logger->log("Reading from file to buffer is complete.");
        }
        else {
            writer->open(destPath);
            logger->log("Запись в файл начата.");


            while ((bytesRead = writer->write(data, bufferSize)) > 0) {
                // handled inside ConcreteFileWriter
            }

            writer->close();
            logger->log("Writing from the buffer to the file is completed.");
        }
    }
    catch (const std::exception& e) {
        logger->log("An exception was thrown: " + std::string(e.what()));
        std::cerr << "An exception: " << e.what() << std::endl;
        throw;
    }
}

/*void InterprocessCopyTool::copy(const std::string& sourcePath, const std::string& destPath) {
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
}*/

/*void InterprocessCopyTool::copy(const std::string& sourcePath, const std::string& destPath) {
    try {
        if (isReader) {
            reader->open(sourcePath);
            logger->log("File reading and buffer writing mode.");

            size_t bytesRead;
            while ((bytesRead = reader->read(data, sizeof(data))) > 0) {
                buffer->write(data, bytesRead);
            }

            buffer->setDoneReading(true);
            reader->close();
            logger->log("Reading from file to buffer is complete.");
        }
        else {
            writer->open(destPath);
            logger->log("Recording mode from buffer to file.");

            size_t bytesRead;
            while ((bytesRead = buffer->read(data, sizeof(data))) > 0) {
                writer->write(data, bytesRead);
            }

            writer->close();
            logger->log("Writing from the buffer to the file is completed.");
        }
    }
    catch (const std::exception& e) {
        logger->log("An exception was thrown: " + std::string(e.what()));
        std::cerr << "An exception: " << e.what() << std::endl;
    }
}*/


