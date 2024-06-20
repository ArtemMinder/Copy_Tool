#pragma once

#include "copyToolInterface.h"
#include <string>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

class InterprocessCopyTool : public CopyToolInterface 
{
public:
    InterprocessCopyTool(const std::string& sharedMemoryName, bool isReader);
    void copy(const std::string& sourcePath, const std::string& destPath) override;

private:
    void readFile(const std::string& sourcePath);
    void writeFile(const std::string& destPath);

    std::string sharedMemoryName;
    bool isReader;

    struct SharedBuffer 
    {
        enum { BufferSize = 16 };
        char buffer[BufferSize];
        size_t size;
        bool doneReading;
        boost::interprocess::interprocess_mutex mutex;
        boost::interprocess::interprocess_condition condEmpty;
        boost::interprocess::interprocess_condition condFull;
    };

    boost::interprocess::managed_shared_memory sharedMemory;
    SharedBuffer* sharedBuffer;
};








