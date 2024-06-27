#include "FileReader.h"
#include <stdexcept>

FileReader::FileReader() {}

FileReader::~FileReader()
{
    close();
}

void FileReader::open(const std::string& filename) 
{
    file.open(filename, std::ios::binary);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

size_t FileReader::read(char* buffer, size_t bufferSize)
{
    file.read(buffer, bufferSize);
    if (file.bad())
    {
        throw std::runtime_error("Failed to read from file");
    }
    return file.gcount();
}

void FileReader::close() 
{
    if (file.is_open()) 
    {
        file.close();
    }
}
