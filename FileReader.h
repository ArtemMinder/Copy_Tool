#pragma once

#include "IReader.h"
#include "IBuffer.h"
#include "ISynchronization.h"
#include <fstream>
#include <stdexcept>

class FileReader : public IReader 
{
public:
    FileReader(IBuffer& buffer, ISynchronization& sync);
    void open(const std::string& path) override;
    size_t read(char* buffer, size_t size) override;
    void close() override;

private:
    std::ifstream file;
    IBuffer& buffer;
    ISynchronization& sync;
};
