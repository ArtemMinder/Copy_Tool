#include "FileWriter.h"

void FileWriter::open(const std::string& path) 
{
    file.open(path, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file for writing: " + path);
    }
}

void FileWriter::write(const char* buffer, size_t size)
{
    file.write(buffer, size);
}

void FileWriter::close()
{
    if (file.is_open())
    {
        file.close();
    }
}
