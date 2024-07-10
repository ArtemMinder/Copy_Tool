#pragma once

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <string>

class InterprocessBuffer {
public:
    explicit InterprocessBuffer(const std::string& name);
    ~InterprocessBuffer();

    char* getData();
    size_t getSize() const;
    void setSize(size_t size);
    void setDoneReading(bool done);
    bool isDoneReading() const;

    boost::interprocess::interprocess_mutex& getMutex();
    boost::interprocess::interprocess_condition& getCondRead();
    boost::interprocess::interprocess_condition& getCondWrite();

private:
    std::string name;
    boost::interprocess::shared_memory_object shm;
    boost::interprocess::mapped_region region;

    struct SharedData {
        boost::interprocess::interprocess_mutex mutex;
        boost::interprocess::interprocess_condition cond_read;
        boost::interprocess::interprocess_condition cond_write;
        bool done_reading = false;
        char data[1024];
        size_t size = 0;
    };
    SharedData* shared_data;
};




