#pragma once

class IBuffer
{
public:
    virtual ~IBuffer() = default;

    virtual char* getData() = 0;
    virtual size_t getSize() const = 0;
    virtual void setSize(size_t size) = 0;
    virtual void setDoneReading(bool done) = 0;
    virtual bool isDoneReading() const = 0;
};
