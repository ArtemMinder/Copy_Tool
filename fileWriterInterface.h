#pragma once

#include <string>

class FileWriterInterface 
{
public:
    virtual ~FileWriterInterface() {}

    virtual bool open(const std::string& filePath) = 0;
    virtual void write(const char* buffer, size_t size) = 0;
    virtual void close() = 0;
};
