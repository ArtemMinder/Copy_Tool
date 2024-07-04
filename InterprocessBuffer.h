#pragma once

#include "IBuffer.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <string>

class InterprocessBuffer : public IBuffer 
{
public:
    InterprocessBuffer(const std::string& sharedMemoryName, size_t bufferSize);
    ~InterprocessBuffer();

    void write(const char* data, size_t dataSize) override;
    size_t read(char* buffer, size_t bufferSize) override;

private:
    boost::interprocess::shared_memory_object sharedMemory;
    boost::interprocess::mapped_region region;
    size_t bufferSize;
};
