#ifndef __REDUCE_H_INCLUDED__
#define __REDUCE_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  Reduce.h    -  header file for Reduce class                  //
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
#include<string>  
#include<iterator>
#include<vector>

class Reduce
{
public: 
	void reduce(std::string key, std::vector<int>::iterator counts);
	void exportz(std::string key, int count);
};
#endif

