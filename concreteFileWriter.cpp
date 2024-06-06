#include "concreteFileWriter.h"
#include <iostream>

ConcreteFileWriter::~ConcreteFileWriter() 
{
    if (file.is_open()) 
    {
        file.close();
    }
}

void ConcreteFileWriter::open(const std::string& filePath) 
{
    file.open(filePath, std::ios::binary);
    if (!file.is_open()) 
    {
        std::cerr << "Failed to open destination file: " << filePath << std::endl;
    }
}

void ConcreteFileWriter::write(const char* buffer, size_t size) 
{
    if (file.is_open()) 
    {
        file.write(buffer, size);
    }
}
