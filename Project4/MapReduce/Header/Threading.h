#ifndef __THREADING_H_INCLUDED__
#define __THREADING_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  Threading.cpp    -  header file for Thread class               //
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
#include <boost/filesystem.hpp>
#include "MapReduceUtils.h"
#include "./IMap.h"
#include "./IReduce.h"

typedef IMap* (*CreateObjectofMap)(); 
typedef IReduce* (*CreateObjectofReduce)();

class Threading {

public:
    void operator()(boost::filesystem::path, std::string, CreateObjectofMap);
    void operator()(boost::filesystem::path, std::string, CreateObjectofReduce);
    void createFile(std::string, std::string);
    void removeFile(std::string);
};

#endif