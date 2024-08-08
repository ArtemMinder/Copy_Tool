#include "InterprocessSynchronization.h"

InterprocessSynchronization::InterprocessSynchronization(const std::string& name)
    : name(name), shm(boost::interprocess::open_or_create, name.c_str(), boost::interprocess::read_write) 
{
    shm.truncate(sizeof(SharedData));
    region = boost::interprocess::mapped_region(shm, boost::interprocess::read_write);
    shared_data = static_cast<SharedData*>(region.get_address());
}

InterprocessSynchronization::~InterprocessSynchronization()
{
    boost::interprocess::shared_memory_object::remove(name.c_str());
}

boost::interprocess::interprocess_mutex& InterprocessSynchronization::getMutex()
{
    return shared_data->mutex;
}

boost::interprocess::interprocess_condition& InterprocessSynchronization::getCondRead()
{
    return shared_data->cond_read;
}

boost::interprocess::interprocess_condition& InterprocessSynchronization::getCondWrite()
{
    return shared_data->cond_write;
}
