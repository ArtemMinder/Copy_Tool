#pragma once

#include "IReader.h"
#include <fstream>
#include <string>

class FileReader : public IReader 
{
public:
    FileReader();
    ~FileReader();

    void open(const std::string& filename) override;
    size_t read(char* buffer, size_t bufferSize) override;
    void close() override;

private:
    std::ifstream file;
};

