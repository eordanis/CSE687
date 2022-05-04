#pragma once
#include <string>
class IMap
{
public:
    virtual ~IMap() { ; }
    virtual void map(std::string, std::string) = 0;
    virtual void setInputFileName(std::string) = 0;
    virtual void setTempFileName(std::string) = 0;
};