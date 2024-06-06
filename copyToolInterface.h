#pragma once

#include <string>

class CopyToolInterface 
{
public:
    virtual ~CopyToolInterface() = default;
    virtual void copy(const std::string& sourcePath, const std::string& destPath) = 0;
};
