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
#include <regex>

class Map
{
	/**
	* Takes the passed value line of text and tokenizes into distinct words
	*
	* @param key - string key for filename.
	* @param value - string value for file line of text.
	* @param tempFilePath - string value for temporary file path
	*/
public: void map(std::string, std::string, std::string);


private:

	/**
	  * Takes the passed token and key filename and writes to memory buffer, periodically writting to a temporary file.
	  *
	  * @param key - string key for filename.
	  * @param value - string value for file line of text.
	  * @param tempFilePath - string value for temporary file path
	  */
	void exportz(std::string, std::string, std::string);

	/**
	  * String special characters and punctations
	  */
	std::string _punctuationAndSpecials = "`~!@#$%^&*()-_=+[]{};':\",.<>/?";

	/**
	 * @brief Tokenize the given vector according to the regex
	 * and remove the empty tokens.
	 *
	 * @param string line to tokenize
	 * @param regex
	 * @return std::vector<std::string> of tokens
	 */
	std::vector<std::string> tokenize(const std::string, const std::regex);

};

#endif
