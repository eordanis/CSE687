#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  Map.h    -  header file for Map class					     //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 2                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,jwashi05}@syr.edu                    //
///////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <map>
#include <regex>

class Map
{
	
public:

	/*
	* Default Constructor for Map
	*/
	Map();

	/*
	* Default Deconstructor for Map
	*/
	~Map();

	/**
	* Takes the passed value line of text and tokenizes into distinct words
	*
	* @param key - string key for input filename.
	* @param value - string value for file line of text.
	*/
	void map(std::string, std::string);

	/**
	* Takes the passed token and key filename and writes to memory buffer, periodically writting to a temporary file.
	*
	* @param key - string key for input filename.
	* @param value - string value for file line of text.
	*/
	void exportz(std::string, std::string);

	/*
	* Set the input file name for the map object
	* @param string input file name
	*/
	void setInputFileName(std::string);

	/*
	* Get the input file name for the map object
	* @return string input file name
	*/
	std::string getInputFileName();

	/*
	* Set the temp file name for the map object
	* @param string temp file name
	*/
	void setTempFileName(std::string);

	/*
	* Get the temp file name for the map object
	* @return string temp file name
	*/
	std::string getTempFileName();

private:

	/**
	* String special characters and punctations
	*/
	const std::string _punctuationAndSpecials = "`~!@#$%^&*()-_=+[]{};':\",.<>/?";

	/**
	* Strings representing the map instance's temporary file name and input file name
	*/
	std::string _tempFileName,_inputFileName;

	/**
	 * Map holding string filename key and vector buffer
	 */
	std::vector<std::string> _exportBuffer;

	/**
	 * @brief Tokenize the given vector according to the regex
	 * and remove the empty tokens.
	 *
	 * @param string line to tokenize
	 * @param regex
	 * @return std::vector<std::string> of tokens
	 */
	std::vector<std::string> tokenize(const std::string, const std::regex);

	/**
	 * flush the buffer out and write to temp file
	 * flush is also called on deconstruct
	 */
	void flush();

};

#endif
