#pragma once

#include <cstddef>

class AbstractBuffer 
{
public:
    virtual ~AbstractBuffer() = default;
    virtual void write(const char* data, size_t dataSize) = 0;
    virtual size_t read(char* buffer, size_t bufferSize) = 0;
};
