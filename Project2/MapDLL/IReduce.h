#pragma once
#include <string>
#include "IMap.h"

class IReduce : IMap
{
public:
    virtual ~IReduce() { ; }
    virtual void setInputFileName(std::string) = 0;
    virtual void setTempFileName(std::string) = 0;
};
