#include "FileWriter.h"

FileWriter::FileWriter(IBuffer& buffer, ISynchronization& sync)
    : buffer(buffer), sync(sync) {}

void FileWriter::open(const std::string& path) 
{
    file.open(path, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file for writing: " + path);
    }
}

size_t FileWriter::write(const char* buf, size_t size)
{
    using namespace boost::interprocess;
    scoped_lock<interprocess_mutex> lock(sync.getMutex());

    while (buffer.getSize() == 0 && !buffer.isDoneReading())
    {
        sync.getCondRead().wait(lock);
    }

    if (buffer.getSize() == 0 && buffer.isDoneReading())
    {
        return 0;
    }

    size_t bytesToWrite = std::min(size, buffer.getSize());
    std::memcpy(const_cast<char*>(buf), buffer.getData(), bytesToWrite);
    file.write(buf, bytesToWrite);
    buffer.setSize(0);
    sync.getCondWrite().notify_one();

    return bytesToWrite;
}

void FileWriter::close() 
{
    if (file.is_open()) 
    {
        file.close();
    }
}
