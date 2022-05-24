#ifndef __EXECUTETHREAD_H_INCLUDED__
#define __EXECUTETHREAD_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  ExecuteThread.h    -  header file for Thread class           //
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

class ExecuteThread {

public:
    void operator()(HINSTANCE, std::string, std::vector<boost::filesystem::path>);
};

#endif
