#pragma once

#include "abstractFileReader.h"
#include <fstream>

class ConcreteFileReader : public AbstractFileReader 
{
public:
    ~ConcreteFileReader();
    void open(const std::string& filePath) override;
    size_t read(char* buffer, size_t size) override;

private:
    std::ifstream file;
};

