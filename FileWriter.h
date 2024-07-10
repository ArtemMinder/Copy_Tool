#pragma once

#include "IWriter.h"
#include "InterprocessBuffer.h"
#include <fstream>
#include <stdexcept>

class FileWriter : public IWriter {
public:
    FileWriter(InterprocessBuffer& buffer);
    void open(const std::string& path) override;
    size_t write(const char* buffer, size_t size) override;
    void close() override;

private:
    std::ofstream file;
    InterprocessBuffer& buffer;
};

