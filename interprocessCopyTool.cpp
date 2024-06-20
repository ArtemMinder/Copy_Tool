#include "interprocessCopyTool.h"
#include "concreteFileReader.h"
#include "concreteFileWriter.h"
#include <iostream>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <mutex>

InterprocessCopyTool::InterprocessCopyTool(const std::string& sharedMemoryName, bool isReader)
    : sharedMemoryName(sharedMemoryName), isReader(isReader), sharedMemory(boost::interprocess::open_or_create, sharedMemoryName.c_str(), 65536) 
{
    if (isReader) 
    {
        sharedBuffer = sharedMemory.find_or_construct<SharedBuffer>("SharedBuffer")();
        sharedBuffer->doneReading = false;
        sharedBuffer->size = 0;
    }
    else 
    {
        sharedBuffer = nullptr;
    }
}

void InterprocessCopyTool::copy(const std::string& sourcePath, const std::string& destPath) 
{
    if (isReader) 
    {
        readFile(sourcePath);
    }
    else
    {
        writeFile(destPath);
    }
}

void InterprocessCopyTool::readFile(const std::string& sourcePath) 
{
    ConcreteFileReader reader;
    reader.open(sourcePath);

    const size_t chunkSize = SharedBuffer::BufferSize;
    std::vector<char> chunk(chunkSize);

    while (true)
    {
        size_t bytesRead = reader.read(chunk.data(), chunkSize);
        if (bytesRead == 0) break; // Конец файла

        std::unique_lock<boost::interprocess::interprocess_mutex> lock(sharedBuffer->mutex);
        sharedBuffer->condEmpty.wait(lock, [this] { return sharedBuffer->size == 0; });

        std::copy(chunk.begin(), chunk.begin() + bytesRead, sharedBuffer->buffer);
        sharedBuffer->size = bytesRead;
        sharedBuffer->condFull.notify_one();
    }

    std::unique_lock<boost::interprocess::interprocess_mutex> lock(sharedBuffer->mutex);
    sharedBuffer->doneReading = true;
    sharedBuffer->condFull.notify_one();
}

void InterprocessCopyTool::writeFile(const std::string& destPath) 
{
    ConcreteFileWriter writer;
    writer.open(destPath);

    while (true) 
    {
        std::unique_lock<boost::interprocess::interprocess_mutex> lock(sharedBuffer->mutex);
        sharedBuffer->condFull.wait(lock, [this] { return sharedBuffer->size > 0 || sharedBuffer->doneReading; });

        if (sharedBuffer->size == 0 && sharedBuffer->doneReading) 
        {
            break; // Все данные прочитаны и записаны
        }

        writer.write(sharedBuffer->buffer, sharedBuffer->size);
        sharedBuffer->size = 0;
        sharedBuffer->condEmpty.notify_one();
    }
}
