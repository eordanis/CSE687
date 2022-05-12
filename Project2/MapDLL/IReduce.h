#pragma once
#include <string>
class IReduce
{
public:
    virtual ~IReduce() { ; }
    virtual void reduce(std::string, std::string) = 0;
    virtual void setInputFileName(std::string) = 0;
    virtual void setTempFileName(std::string) = 0;
};
