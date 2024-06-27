#include "FileWriter.h"
#include <stdexcept>

FileWriter::FileWriter() {}

FileWriter::~FileWriter() 
{
    close();
}

void FileWriter::open(const std::string& filename) 
{
    file.open(filename, std::ios::binary);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

void FileWriter::write(const char* data, size_t dataSize) 
{
    file.write(data, dataSize);
    if (file.bad()) 
    {
        throw std::runtime_error("Failed to write to file");
    }
}

void FileWriter::close() 
{
    if (file.is_open())
    {
        file.close();
    }
}
