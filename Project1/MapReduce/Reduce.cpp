///////////////////////////////////////////////////////////////////
//  Reduce.cpp -  Reduce Class                                   //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 1                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,jwashi05}@syr.edu                    //
///////////////////////////////////////////////////////////////////

#pragma once
#include "Reduce.h"

void Reduce::reduce(std::string key, std::vector<int>::iterator counts)
{
}

void Reduce::exportz(std::string key, int count)
{
}

/* The reduce class will have a method reduce() that will take a string with one key and an iterator of integers.
The reduce function should sum all the values in the iterator and then call an export() function (different from the Map class).
The export function will take two parameters, the key and resulting reduced value, and write the result out to the output directory.
Upon success an additional empty file SUCCESS will be written out to the output directory.
The reduce method itself should not directly deal with any File IO. */
