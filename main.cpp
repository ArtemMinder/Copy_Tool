#include <iostream>
#include "copyToolFactory.h"

int main(int argc, char* argv[])
{
   if (argc != 3) 
   {
        std::cerr << "Usage: " << argv[0] << " <source file> <destination file>" << std::endl;
        return 1;
   }

    const std::string sourcePath = argv[1];
    const std::string destPath = argv[2];

    CopyToolFactory factory;
    auto copyTool = factory.createCopyTool();
    copyTool->copy(sourcePath, destPath);

    return 0;
}