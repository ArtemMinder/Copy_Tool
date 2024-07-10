#pragma once

#include <cstddef>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

class IBuffer 
{
public:
    virtual ~IBuffer() = default;
    virtual char* getData() = 0;
    virtual size_t getSize() const = 0;
    virtual void setSize(size_t size) = 0;
    virtual void setDoneReading(bool done) = 0;
    virtual bool isDoneReading() const = 0;
    virtual boost::interprocess::interprocess_mutex& getMutex() = 0;
    virtual boost::interprocess::interprocess_condition& getCondRead() = 0;
    virtual boost::interprocess::interprocess_condition& getCondWrite() = 0;
};