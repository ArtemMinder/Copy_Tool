#include "InterprocessBuffer.h"
#include <stdexcept>
#include <cstring>

InterprocessBuffer::InterprocessBuffer(const std::string& sharedMemoryName, size_t bufferSize)
    : bufferSize(bufferSize) 
{
    try 
    {
        boost::interprocess::shared_memory_object::remove(sharedMemoryName.c_str());
        sharedMemory = boost::interprocess::shared_memory_object(
            boost::interprocess::create_only, sharedMemoryName.c_str(), boost::interprocess::read_write);

        sharedMemory.truncate(bufferSize);
        region = boost::interprocess::mapped_region(sharedMemory, boost::interprocess::read_write);
    }
    catch (const std::exception& e) 
    {
        throw std::runtime_error("Failed to create shared memory: " + std::string(e.what()));
    }
}

InterprocessBuffer::~InterprocessBuffer() 
{
    boost::interprocess::shared_memory_object::remove(sharedMemory.get_name());
}

void InterprocessBuffer::write(const char* data, size_t dataSize)
{
    if (dataSize > bufferSize) 
    {
        throw std::runtime_error("Data size exceeds buffer size");
    }
    std::memcpy(region.get_address(), data, dataSize);
}

size_t InterprocessBuffer::read(char* buffer, size_t bufferSize) 
{
    size_t dataSize = std::min(bufferSize, this->bufferSize);
    std::memcpy(buffer, region.get_address(), dataSize);
    return dataSize;
}
