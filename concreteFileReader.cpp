#include "concreteFileReader.h"

ConcreteFileReader::ConcreteFileReader() {}

ConcreteFileReader::~ConcreteFileReader() 
{
    if (fileStream.is_open()) 
    {
        fileStream.close();
    }
}

void ConcreteFileReader::open(const std::string& filePath) 
{
    fileStream.open(filePath, std::ios::binary);
}

size_t ConcreteFileReader::read(char* buffer, size_t bufferSize)
{
    fileStream.read(buffer, bufferSize);
    return fileStream.gcount();
}
