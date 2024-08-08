#include "InterprocessBuffer.h"

InterprocessBuffer::InterprocessBuffer(const std::string& name)
    : name(name), shm(boost::interprocess::open_or_create, name.c_str(), boost::interprocess::read_write)
{
    shm.truncate(sizeof(SharedData));
    region = boost::interprocess::mapped_region(shm, boost::interprocess::read_write);
    shared_data = static_cast<SharedData*>(region.get_address());
}

InterprocessBuffer::~InterprocessBuffer()
{
    boost::interprocess::shared_memory_object::remove(name.c_str());
}

char* InterprocessBuffer::getData()
{
    return shared_data->data;
}

size_t InterprocessBuffer::getSize() const 
{
    return shared_data->size;
}

void InterprocessBuffer::setSize(size_t size) 
{
    shared_data->size = size;
}

void InterprocessBuffer::setDoneReading(bool done)
{
    shared_data->done_reading = done;
}

bool InterprocessBuffer::isDoneReading() const
{
    return shared_data->done_reading;
}
