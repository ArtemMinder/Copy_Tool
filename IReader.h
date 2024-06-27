#pragma once

#include <cstddef>
#include <string>

class IReader 
{
public:
    virtual ~IReader() = default;
    virtual void open(const std::string& filename) = 0;
    virtual size_t read(char* buffer, size_t bufferSize) = 0;
    virtual void close() = 0;
};


