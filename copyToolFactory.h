#pragma once

#include <memory>
#include "abstractCopyToolFactory.h"
#include "copyTool.h"

class CopyToolFactory : public AbstractCopyToolFactory 
{
public:
    std::unique_ptr<CopyToolInterface> createCopyTool() const override 
    {
        return std::make_unique<CopyTool>();
    }
};

