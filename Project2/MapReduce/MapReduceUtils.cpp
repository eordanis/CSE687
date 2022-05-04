///////////////////////////////////////////////////////////////////
//  MapReduceUtils.cpp    -  MapReduceUtils Class                //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 2                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                jwashi05@syr.edu                               //
///////////////////////////////////////////////////////////////////

#pragma once

#include "MapReduceUtils.h"
#include <string>
#include <boost/log/trivial.hpp>

MapReduceUtils::MapReduceUtils()
{
}

MapReduceUtils::~MapReduceUtils()
{
}

void MapReduceUtils::throwException(std::string method, std::string exception)
{
	BOOST_LOG_TRIVIAL(error) << method << ":\t  " << exception;
	exit(1);
}

void MapReduceUtils::logMessage(std::string msg)
{
	BOOST_LOG_TRIVIAL(info) << msg;
}
