#include "InterprocessBuffer.h"

InterprocessBuffer::InterprocessBuffer(const std::string& name)
    : name(name)
{
    using namespace boost::interprocess;

    shared_memory_object::remove(name.c_str());
    shm = shared_memory_object(create_only, name.c_str(), read_write);
    shm.truncate(sizeof(SharedData));

    region = mapped_region(shm, read_write);
    sharedData = new (region.get_address()) SharedData;
    sharedData->dataReady = false;
    sharedData->doneReading = false;
}

InterprocessBuffer::~InterprocessBuffer() 
{
    boost::interprocess::shared_memory_object::remove(name.c_str());
}

void InterprocessBuffer::write(const char* data, size_t size) 
{
    if (size > sizeof(sharedData->data)) 
    {
        throw std::runtime_error("Data size exceeds buffer size.");
    }

    boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(sharedData->mutex);
    std::memcpy(sharedData->data, data, size);
    sharedData->dataReady = true;
    sharedData->cond.notify_one();
    sharedData->cond.wait(lock, [this] { return !sharedData->dataReady; });
}

size_t InterprocessBuffer::read(char* data, size_t size) 
{
    boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(sharedData->mutex);
    sharedData->cond.wait(lock, [this] { return sharedData->dataReady || sharedData->doneReading; });
    if (sharedData->doneReading && !sharedData->dataReady) 
    {
        return 0;
    }
    std::memcpy(data, sharedData->data, size);
    sharedData->dataReady = false;
    sharedData->cond.notify_one();
    return size;
}

void InterprocessBuffer::setDoneReading(bool done)
{
    boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(sharedData->mutex);
    sharedData->doneReading = done;
    sharedData->cond.notify_all();
}

bool InterprocessBuffer::isDoneReading() const 
{
    boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(sharedData->mutex);
    return sharedData->doneReading;
}
