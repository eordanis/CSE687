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
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <boost/log/trivial.hpp>
#include <boost/algorithm/string.hpp>
#include "FileManagement.h"

Map::Map()
{
}

Map::Map(std::string fileName, std::string tempFileName)
{
    _fileName = fileName;
    _tempFileName = tempFileName;
}

Map::~Map()
{
}

void Map::map(std::string key, std::string value)
{
    //punctuation and special characters to remove
    std::string regex = _punctuationAndSpecials;

    // trim
    boost::trim(value);

    // remove all special characters from value string
    value.erase(std::remove_if(value.begin(), value.end(),
        [&regex](const char& c) {
            return regex.find(c) != std::string::npos;
        }),
        value.end());

    //if line is not empty
    if (value.size() > 0)
    {
        //convert to lowercase
        boost::algorithm::to_lower(value); // modifies str

        const std::regex re(R"([\s]+)");

        // Function Call
        const std::vector<std::string> tokenized =
            tokenize(value, re);

        for (std::string token : tokenized) {
            //BOOST_LOG_TRIVIAL(debug) << "Token: \t\"" << token << "\"" << std::endl; //debug
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
    if (!_purgeExportBuffer){
        std::string value = "(" + token + ",1)\n";
        //BOOST_LOG_TRIVIAL(debug) << "Value to export: \t\"" << value << "\"" << std::endl; //debug
        //TODO store value in buffer of size and write to file when buffer is full.
        _exportBuffer.emplace_back(value);
    }

    if (_exportBuffer.size() == _exportBufferMaxSize || _purgeExportBuffer) {
        FileManagement fm;
        std::stringstream result;
        copy(_exportBuffer.begin(), _exportBuffer.end(), std::ostream_iterator<std::string>(result, ""));
        fm.writeToFile(_tempFileName, result.str());
        _exportBuffer.clear();
    }
}

void Map::setPurgeFlag(bool flag)
{
    _purgeExportBuffer = flag;
}

size_t Map::getExportBufferSize()
{
    return _exportBuffer.size();
}

/* The map class will contain a public method map(), that accepts a key and value.
The key will be the file name and the value will be a single line of raw data from the file.
The map() function will tokenize the value into distinct words (remove punctuation, whitespace and capitalization).
The map() function will call a second function export that takes a key and value as two parameters.
The export function will buffer output in memory and periodically write the data out to disk (periodicity can be based on the size of the buffer).
The intermediate data will be written to the temporary directory (specified via command line). */
