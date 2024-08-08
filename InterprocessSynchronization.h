#pragma once

#include "ISynchronization.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <string>

class InterprocessSynchronization : public ISynchronization 
{
public:
    explicit InterprocessSynchronization(const std::string& name);
    ~InterprocessSynchronization();

    boost::interprocess::interprocess_mutex& getMutex() override;
    boost::interprocess::interprocess_condition& getCondRead() override;
    boost::interprocess::interprocess_condition& getCondWrite() override;

private:
    std::string name;
    boost::interprocess::shared_memory_object shm;
    boost::interprocess::mapped_region region;

    struct SharedData 
    {
        boost::interprocess::interprocess_mutex mutex;
        boost::interprocess::interprocess_condition cond_read;
        boost::interprocess::interprocess_condition cond_write;
    };
    SharedData* shared_data;
};



