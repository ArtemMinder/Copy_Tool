#pragma once

#include "copyToolInterface.h"
#include "abstractFileReader.h"
#include "abstractFileWriter.h"
#include "concreteFileReader.h"
#include "concreteFileWriter.h"
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

class CopyTool : public CopyToolInterface 
{
public:
    void copy(const std::string& sourcePath, const std::string& destPath) override;

private:
    void readFile(const std::string& sourcePath);
    void writeFile(const std::string& destPath);

    std::vector<char> buffer;
    std::mutex bufferMutex;
    std::condition_variable bufferNotEmpty;
    std::condition_variable bufferEmpty;
    bool doneReading = false;
};

