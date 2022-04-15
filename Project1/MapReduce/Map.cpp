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
#include <string.h>
#include <boost/log/trivial.hpp>
#include <boost/algorithm/string.hpp>

void Map::map(std::string key, std::string value)
{
    //punctuation and special characters to remove
    std::string regex = Map::punctuationAndSpecials;

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

        //prepate value to be tokenized
        char* value_c = new char[value.size() + 1];
        strcpy_s(value_c, strlen(value_c) * sizeof(char), value.c_str());
        char* token;
        char* rest = value_c;
        //iterate over tokens
        while ((token = strtok_s(rest, " ", &rest)))
        {
            BOOST_LOG_TRIVIAL(debug) << "Token: \t\"" << token << "\"" << std::endl; //debug
            exportz(key, token);

        }
    }
}

void Map::exportz(std::string key, char* token)
{

}

/* The map class will contain a public method map(), that accepts a key and value.
The key will be the file name and the value will be a single line of raw data from the file.
The map() function will tokenize the value into distinct words (remove punctuation, whitespace and capitalization).
The map() function will call a second function export that takes a key and value as two parameters.
The export function will buffer output in memory and periodically write the data out to disk (periodicity can be based on the size of the buffer).
The intermediate data will be written to the temporary directory (specified via command line). */
