#pragma once

#include "IWriter.h"
#include <fstream>
#include <string>

#include "IWriter.h"
#include <fstream>
#include <stdexcept>

class FileWriter : public IWriter 
{
public:
    void open(const std::string& path) override;
    void write(const char* buffer, size_t size) override;
    void close() override;

private:
    std::ofstream file;
};

