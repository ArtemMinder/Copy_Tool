#pragma once

#include <string>
#include <fstream>

class ConcreteFileWriter 
{
public:
    ConcreteFileWriter();
    ~ConcreteFileWriter();

    void open(const std::string& filePath);
    void write(const char* buffer, size_t size);

private:
    std::ofstream fileStream;
};




