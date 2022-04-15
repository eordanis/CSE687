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
//                {sleordan,jwashi05}@syr.edu                    //
///////////////////////////////////////////////////////////////////

#pragma once
#include <string>
class Map
{
	/**
	* Takes the passed value line of text and tokenizes into distinct words
	*
	* @param key - string key for filename.
	* @param value - string value for file line of text.
	*/
public: void map(std::string key, std::string value);

	  /**
	  * Takes the passed token and key filename and writes to memory buffer, periodically writting to a temporary file.
	  *
	  * @param key - string key for filename.
	  * @param value - string value for file line of text.
	  */
private: void exportz(std::string key, char* token);

//punctuation and special characters to remove
private: std::string punctuationAndSpecials = "`~!@#$%^&*()-_=+[]{};':\",.<>/?";


};

#endif
