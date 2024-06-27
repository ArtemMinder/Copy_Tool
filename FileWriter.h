#pragma once

#include "IWriter.h"
#include <fstream>
#include <string>

class FileWriter : public IWriter 
{
public:
    FileWriter();
    ~FileWriter();

    void open(const std::string& filename) override;
    void write(const char* data, size_t dataSize) override;
    void close() override;

private:
    std::ofstream file;
};
