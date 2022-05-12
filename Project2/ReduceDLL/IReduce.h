#pragma once
#include <string>

class IReduce
{
public:
    virtual ~IReduce() { ; }
    virtual void setOutputFileName(std::string) = 0;
    virtual void setTempFileName(std::string) = 0;
    virtual std::string getReduceData(std::string) = 0;
    virtual void insertKey(std::string) = 0;
    virtual void exportz(std::string, bool) = 0;
    virtual size_t getExportBufferSize() = 0;
    virtual void purgeBuffer(std::string) = 0;

    std::string _tempFileName = "";
    std::string _outputFileName = "";
};