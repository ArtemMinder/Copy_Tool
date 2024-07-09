#pragma once

#include <string>

class IBuffer
{
public:
    virtual ~IBuffer() = default;
    virtual void write(const char* data, size_t size) = 0;
    virtual size_t read(char* data, size_t size) = 0;
    virtual void setDoneReading(bool done) = 0;
    virtual bool isDoneReading() const = 0;
};
