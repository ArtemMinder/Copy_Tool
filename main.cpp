#include <iostream>
#include <memory>
#include "interprocessCopyToolFactory.h"

int main(int argc, char* argv[]) {
    std::string sourcePath = "source.txt";      
    std::string destPath = "destination.txt";   
    std::string sharedMemoryName = "MySharedMemory"; 

 
    InterprocessCopyToolFactory factory(sharedMemoryName);
    std::unique_ptr<CopyToolInterface> copyTool = factory.createCopyTool();

    copyTool->copy(sourcePath, destPath);

    return 0;
}