#include "InterprocessBuffer.h"
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>

InterprocessBuffer::InterprocessBuffer(const std::string& name)
    : name(name) {
    using namespace boost::interprocess;

    shared_memory_object::remove(name.c_str());
    shm = shared_memory_object(create_only, name.c_str(), read_write);
    shm.truncate(sizeof(SharedData));

    region = mapped_region(shm, read_write);
    void* addr = region.get_address();
    shared_data = new (addr) SharedData;
}

InterprocessBuffer::~InterprocessBuffer() {
    boost::interprocess::shared_memory_object::remove(name.c_str());
}

char* InterprocessBuffer::getData() {
    return shared_data->data;
}

size_t InterprocessBuffer::getSize() const {
    return shared_data->size;
}

void InterprocessBuffer::setSize(size_t size) {
    shared_data->size = size;
}

void InterprocessBuffer::setDoneReading(bool done) {
    shared_data->done_reading = done;
    shared_data->cond_read.notify_all();
}

bool InterprocessBuffer::isDoneReading() const {
    return shared_data->done_reading;
}

boost::interprocess::interprocess_mutex& InterprocessBuffer::getMutex() {
    return shared_data->mutex;
}

boost::interprocess::interprocess_condition& InterprocessBuffer::getCondRead() {
    return shared_data->cond_read;
}

boost::interprocess::interprocess_condition& InterprocessBuffer::getCondWrite() {
    return shared_data->cond_write;
}
