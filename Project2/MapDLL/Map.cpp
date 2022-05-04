///////////////////////////////////////////////////////////////////
//  Map.cpp -  Map Class                                         //
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
#include "Map.h"
#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

Map::Map()
{
}

Map::~Map()
{
	flush();
}

MAPLIBRARY_API void Map::map(std::string key, std::string value)
{
	//punctuation and special characters to remove
	std::string regex = _punctuationAndSpecials;

	// remove all special characters from value string
	value.erase(std::remove_if(value.begin(), value.end(),
		[&regex](const char& c) {
			return regex.find(c) != std::string::npos;
		}),
		value.end());

	// trim beginging/end whitespacing
	value.erase(value.find_last_not_of(' ') + 1);
	value.erase(0, value.find_first_not_of(' '));

	//if line is not empty
	if (value.size() > 0)
	{
		//convert to lowercase and storing the result in destination string
		std::transform(value.begin(), value.end(), value.begin(),
			[](unsigned char c) { return std::tolower(c); });

		const std::regex re(R"([\s]+)");

		// Function Call
		const std::vector<std::string> tokenized =
			tokenize(value, re);

		for (std::string token : tokenized) {
			exportz(key, token);
		}
	}
}

std::vector<std::string> Map::tokenize(const std::string str, const std::regex re)
{
	std::sregex_token_iterator it{ str.begin(),
							str.end(), re, -1 };
	std::vector<std::string> tokenized{ it, {} };

	// Additional check to remove empty strings
	tokenized.erase(
		std::remove_if(tokenized.begin(),
			tokenized.end(),
			[](std::string const& s) {
				return s.size() == 0;
			}),
		tokenized.end());

	return tokenized;
}

void Map::exportz(std::string key, std::string token)
{
	if (token != "") {
		std::string value = "(" + token + ",1)\n";
		_exportBuffer.emplace_back(value);
	}

	if (_exportBuffer.size() == 50) {
		flush();
	}
}

void Map::setInputFileName(std::string inputFileName)
{
	_inputFileName = inputFileName;
}

std::string Map::getInputFileName()
{
	return _inputFileName;
}

void Map::setTempFileName(std::string tempFileName)
{
	_tempFileName = tempFileName;
}

std::string Map::getTempFileName()
{
	return _tempFileName;

}

void Map::flush()
{
	if (_exportBuffer.size() > 0) {
		std::stringstream result;
		copy(_exportBuffer.begin(), _exportBuffer.end(), std::ostream_iterator<std::string>(result, ""));
		std::string resultStr = result.str();
		//write to temp file
		std::fstream fs;
		fs.open(_tempFileName, std::fstream::in | std::fstream::out | std::fstream::app);
		fs << resultStr;
		fs.close();
		//clear buffer
		_exportBuffer.clear();
		//clear result string stream
		result.clear();
	}
}

/* The map class will contain a public method map(), that accepts a key and value.
The key will be the file name and the value will be a single line of raw data from the file.
The map() function will tokenize the value into distinct words (remove punctuation, whitespace and capitalization).
The map() function will call a second function export that takes a key and value as two parameters.
The export function will buffer output in memory and periodically write the data out to disk (periodicity can be based on the size of the buffer).
The intermediate data will be written to the temporary directory (specified via command line). */
