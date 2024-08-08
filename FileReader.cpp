#include "FileReader.h"

FileReader::FileReader(IBuffer& buffer, ISynchronization& sync)
    : buffer(buffer), sync(sync) {}

void FileReader::open(const std::string& path) 
{
    file.open(path, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file for reading: " + path);
    }
}

size_t FileReader::read(char* buf, size_t size) 
{
    file.read(buf, size);
    size_t bytesRead = file.gcount();

    if (bytesRead > 0) {
        using namespace boost::interprocess;
        scoped_lock<interprocess_mutex> lock(sync.getMutex());

        while (buffer.getSize() > 0) 
        {
            sync.getCondWrite().wait(lock);
        }

        std::memcpy(buffer.getData(), buf, bytesRead);
        buffer.setSize(bytesRead);
        sync.getCondRead().notify_one();
    }

    return bytesRead;
}

void FileReader::close()
{
    if (file.is_open())
    {
        file.close();
    }
}
