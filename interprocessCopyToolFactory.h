#pragma once

#include <memory>
#include "abstractCopyToolFactory.h"
#include "interprocessCopyTool.h"
#include <boost/interprocess/shared_memory_object.hpp>

class InterprocessCopyToolFactory : public AbstractCopyToolFactory 
{
public:
    InterprocessCopyToolFactory(const std::string& sharedMemoryName)
        : sharedMemoryName(sharedMemoryName) {}

    std::unique_ptr<CopyToolInterface> createCopyTool() const override
    {
        boost::interprocess::shared_memory_object::remove(sharedMemoryName.c_str());
        return std::make_unique<InterprocessCopyTool>(sharedMemoryName, true);
    }

private:
    std::string sharedMemoryName;
};





