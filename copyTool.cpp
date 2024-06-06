#include "copyTool.h"

void CopyTool::copy(const std::string& sourcePath, const std::string& destPath) 
{
    std::thread reader(&CopyTool::readFile, this, std::ref(sourcePath));
    std::thread writer(&CopyTool::writeFile, this, std::ref(destPath));

    reader.join();
    writer.join();
}

void CopyTool::readFile(const std::string& sourcePath) 
{
    ConcreteFileReader reader;
    reader.open(sourcePath);

    const size_t chunkSize = 16384;
    std::vector<char> chunk(chunkSize);

    while (true) 
    {
        size_t bytesRead = reader.read(chunk.data(), chunkSize);
        if (bytesRead == 0) break;

        std::unique_lock<std::mutex> lock(bufferMutex);
        bufferNotEmpty.wait(lock, [this] { return buffer.empty(); });

        buffer.assign(chunk.begin(), chunk.begin() + bytesRead);
        bufferEmpty.notify_one();
    }

    std::unique_lock<std::mutex> lock(bufferMutex);
    doneReading = true;
    bufferEmpty.notify_one();
}

void CopyTool::writeFile(const std::string& destPath) {
    ConcreteFileWriter writer;
    writer.open(destPath);

    while (true) {
        std::unique_lock<std::mutex> lock(bufferMutex);
        bufferEmpty.wait(lock, [this] { return !buffer.empty() || doneReading; });

        if (buffer.empty() && doneReading) {
            break;
        }

        writer.write(buffer.data(), buffer.size());
        buffer.clear();
        bufferNotEmpty.notify_one();
    }
}
