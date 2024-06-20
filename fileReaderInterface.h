#pragma once

#include <string>

class FileReaderInterface 
{
public:
    virtual ~FileReaderInterface() {}

    virtual bool open(const std::string& filePath) = 0;
    virtual size_t read(char* buffer, size_t size) = 0;
    virtual void close() = 0;
};

