#pragma once

#include <memory>
#include "abstractCopyToolFactory.h"
#include "interprocessCopyTool.h"
#include "interprocessCopyToolFactory.h"

class CopyToolFactory : public AbstractCopyToolFactory 
{
public:
    std::unique_ptr<CopyToolInterface> createCopyTool() const override 
    {
        return std::make_unique<InterprocessCopyTool>();
    }
};

