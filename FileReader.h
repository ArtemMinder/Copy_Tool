#pragma once

#include "IReader.h"
#include "InterprocessBuffer.h"
#include <fstream>
#include <stdexcept>

class FileReader : public IReader 
{
public:
    FileReader(InterprocessBuffer& buffer);
    void open(const std::string& path) override;
    size_t read(char* buffer, size_t size) override;
    void close() override;

private:
    std::ifstream file;
    InterprocessBuffer& buffer;
};


