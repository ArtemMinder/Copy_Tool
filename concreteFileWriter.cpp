#include "concreteFileWriter.h"

ConcreteFileWriter::ConcreteFileWriter() {}

ConcreteFileWriter::~ConcreteFileWriter() 
{
    if (fileStream.is_open()) 
    {
        fileStream.close();
    }
}

void ConcreteFileWriter::open(const std::string& filePath) 
{
    fileStream.open(filePath, std::ios::binary);
}

void ConcreteFileWriter::write(const char* buffer, size_t size) 
{
    fileStream.write(buffer, size);
}
