#pragma once

#include <string>

class AbstractFileWriter 
{
public:
    virtual ~AbstractFileWriter() = default;
    virtual void open(const std::string& filePath) = 0;
    virtual void write(const char* buffer, size_t size) = 0;
};
