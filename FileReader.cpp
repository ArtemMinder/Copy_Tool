#include "FileReader.h"

void FileReader::open(const std::string& path)
{
    file.open(path, std::ios::binary);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Cannot open file for reading: " + path);
    }
}

size_t FileReader::read(char* buffer, size_t size) 
{
    file.read(buffer, size);
    return file.gcount();
}

void FileReader::close() 
{
    if (file.is_open()) 
    {
        file.close();
    }
}
