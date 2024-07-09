#pragma once

#include <string>

class IReader 
{
public:
    virtual ~IReader() = default;
    virtual void open(const std::string& path) = 0;
    virtual size_t read(char* buffer, size_t size) = 0;
    virtual void close() = 0;
};


