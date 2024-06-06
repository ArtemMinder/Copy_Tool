#pragma once

#include "abstractFileWriter.h"
#include <fstream>

class ConcreteFileWriter : public AbstractFileWriter 
{
public:
    ~ConcreteFileWriter();
    void open(const std::string& filePath) override;
    void write(const char* buffer, size_t size) override;

private:
    std::ofstream file;
};

