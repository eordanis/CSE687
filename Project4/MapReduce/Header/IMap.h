#ifndef __IMAP_DLL_H_INCLUDED__
#define __IMAP_DLL_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  IMap.h    -    header file for IMap                          //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 3                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,jwashi05}@syr.edu                    //
///////////////////////////////////////////////////////////////////

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

#endif