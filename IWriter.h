#pragma once

#include <string>

class IWriter {
public:
    virtual ~IWriter() {}
    virtual void open(const std::string& path) = 0;
    virtual size_t write(const char* buffer, size_t size) = 0;
    virtual void close() = 0;
};





