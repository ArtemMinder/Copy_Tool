#pragma once

#include "IBuffer.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <string>

class InterprocessBuffer : public IBuffer
{
public:
    explicit InterprocessBuffer(const std::string& name);
    ~InterprocessBuffer();

    char* getData() override;
    size_t getSize() const override;
    void setSize(size_t size) override;
    void setDoneReading(bool done) override;
    bool isDoneReading() const override;

private:
    std::string name;
    boost::interprocess::shared_memory_object shm;
    boost::interprocess::mapped_region region;

    struct SharedData 
    {
        bool done_reading = false;
        char data[1024];
        size_t size = 0;
    };
    SharedData* shared_data;
};
