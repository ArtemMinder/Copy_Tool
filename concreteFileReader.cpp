#include "concreteFileReader.h"
#include <iostream>

ConcreteFileReader::~ConcreteFileReader() 
{
    if (file.is_open()) 
    {
        file.close();
    }
}

void ConcreteFileReader::open(const std::string& filePath) 
{
    file.open(filePath, std::ios::binary);
    if (!file.is_open()) 
    {
        std::cerr << "Failed to open source file: " << filePath << std::endl;
    }
}

size_t ConcreteFileReader::read(char* buffer, size_t size) 
{
    if (!file.is_open()) return 0;
    file.read(buffer, size);
    return file.gcount();
}