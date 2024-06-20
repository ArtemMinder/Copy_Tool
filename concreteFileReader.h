#pragma once

#include <string>
#include <fstream>

class ConcreteFileReader 
{
public:
    ConcreteFileReader();
    ~ConcreteFileReader();

    void open(const std::string& filePath);
    size_t read(char* buffer, size_t bufferSize);

private:
    std::ifstream fileStream;
};




