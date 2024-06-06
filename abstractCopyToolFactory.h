#pragma once

#include <memory>
#include "copyToolInterface.h"

class AbstractCopyToolFactory 
{
public:
    virtual ~AbstractCopyToolFactory() = default;
    virtual std::unique_ptr<CopyToolInterface> createCopyTool() const = 0;
};

