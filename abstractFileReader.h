#pragma once

#include <string>

class AbstractFileReader 
{
public:
    virtual ~AbstractFileReader() = default;
    virtual void open(const std::string& filePath) = 0;
    virtual size_t read(char* buffer, size_t size) = 0;
};
