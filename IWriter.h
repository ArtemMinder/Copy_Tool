#pragma once

#include <cstddef>
#include <string>

class IWriter 
{
public:
    virtual ~IWriter() = default;
    virtual void open(const std::string& filename) = 0;
    virtual void write(const char* data, size_t dataSize) = 0;
    virtual void close() = 0;
};


