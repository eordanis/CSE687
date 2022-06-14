#ifndef __IREDUCE_DLL_H_INCLUDED__
#define __IREDUCE_DLL_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  IReduce.h    -    header file for IReduce                    //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 4                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,jwashi05}@syr.edu                    //
///////////////////////////////////////////////////////////////////

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
    virtual void resetMap() = 0;

    std::string _tempFileName = "";
    std::string _outputFileName = "";
};

#endif