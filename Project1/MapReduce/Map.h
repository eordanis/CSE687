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
	* Parameterized Constructor for Map
	* @param string filename of source file
	* @param string tempFileName of temporary file created
	*/
	Map(std::string, std::string);

	/*
	* Default Deconstructor for Map
	*/
	~Map();

	/**
	* Takes the passed value line of text and tokenizes into distinct words
	*
	* @param key - string key for filename.
	* @param value - string value for file line of text.
	*/
	void map(std::string, std::string);

	/**
	* Takes the passed token and key filename and writes to memory buffer, periodically writting to a temporary file.
	*
	* @param key - string key for filename.
	* @param value - string value for file line of text.
	*/
	void exportz(std::string, std::string);

	/*
	* Set the purge flag to the passed boolean value
	*/
	void setPurgeFlag(bool);

	/*
	* Return the current size of the export buffer
	*/
	size_t getExportBufferSize();

private:

	/**
	 * Max size of export buffer
	 */
	int _exportBufferMaxSize = 50;

	/**
	 * Boolean indicating if we need to purge export buffer
	 */
	bool _purgeExportBuffer = false;

	/**
	* String special characters and punctations
	*/
	std::string _punctuationAndSpecials = "`~!@#$%^&*()-_=+[]{};':\",.<>/?";

	/**
	* Strings representing the map instance's temporary file name and source text file name
	*/
	std::string _tempFileName,_fileName;

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

};

#endif
