#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  Map.h    -  header file for Map class					     //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 1                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,}@syr.edu                            //
///////////////////////////////////////////////////////////////////

#pragma once
#include <string>
class Map
{
public: 
	void map(std::string key, std::string value);
	void exportz();
};

#endif
