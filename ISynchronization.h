#pragma once

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

class ISynchronization 
{
public:
    virtual ~ISynchronization() = default;
    virtual boost::interprocess::interprocess_mutex& getMutex() = 0;
    virtual boost::interprocess::interprocess_condition& getCondRead() = 0;
    virtual boost::interprocess::interprocess_condition& getCondWrite() = 0;
};
