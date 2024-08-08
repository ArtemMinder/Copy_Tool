#pragma once

#include "IWriter.h"
#include "IBuffer.h"
#include "ISynchronization.h"
#include <fstream>
#include <stdexcept>

class FileWriter : public IWriter
{
public:
    FileWriter(IBuffer& buffer, ISynchronization& sync);
    void open(const std::string& path) override;
    size_t write(const char* buffer, size_t size) override;
    void close() override;

private:
    std::ofstream file;
    IBuffer& buffer;
    ISynchronization& sync;
};


