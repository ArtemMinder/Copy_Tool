#pragma once

#include "IBuffer.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <cstring>
#include <stdexcept>

class InterprocessBuffer : public IBuffer
{
public:
    explicit InterprocessBuffer(const std::string& name);
    ~InterprocessBuffer();

    void write(const char* data, size_t size) override;
    size_t read(char* data, size_t size) override;
    void setDoneReading(bool done) override;
    bool isDoneReading() const override;

private:
    struct SharedData 
    {
        boost::interprocess::interprocess_mutex mutex;
        boost::interprocess::interprocess_condition cond;
        char data[1024];
        bool dataReady;
        bool doneReading;
    };

    std::string name;
    boost::interprocess::shared_memory_object shm;
    boost::interprocess::mapped_region region;
    SharedData* sharedData;
};



