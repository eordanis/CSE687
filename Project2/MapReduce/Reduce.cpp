///////////////////////////////////////////////////////////////////
//  Reduce.cpp -  Reduce Class                                   //
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
#include "Reduce.h"
#include <boost/algorithm/string.hpp>
#include <iterator>
#include <map>
#include <sstream>
#include <boost/mpl/pair.hpp>
#include "FileManagement.h"

Reduce::Reduce()
{
}

Reduce::~Reduce()
{
}

Reduce::Reduce(std::string fileName, std::string outFileName)
{
    _fileName = fileName;
    _outFileName = outFileName;
}

std::string Reduce::getReduceData(std::string entry)
{
    boost::erase_all(entry, "(");
    boost::erase_all(entry, ")");
    boost::erase_all(entry, ",1");

    return entry;
}

void Reduce::insertKey(std::string key)
{
    std::map<std::string, int>::iterator iterate;

    if (reduceMap.count(key) == 0) {
        reduceMap.insert(std::pair<std::string, int>(key, 1));
    }
    else {
        iterate = reduceMap.find(key);
        iterate->second = iterate->second++;
    }


}

void Reduce::exportz(std::string filename, bool purge)
{
    std::map<std::string, int>::iterator iterate;

    for (iterate = reduceMap.begin(); iterate != reduceMap.end(); ++iterate) {

        if (!purge) {
            std::string value = "(" + iterate->first + "," + std::to_string(iterate->second) + ")\n";
            _exportBuffer.emplace_back(value);
        }

        if (_exportBuffer.size() == _exportBufferMaxSize || purge) {
            FileManagement fm;
            std::stringstream result;
            copy(_exportBuffer.begin(), _exportBuffer.end(), std::ostream_iterator<std::string>(result, ""));
            fm.writeToFile(_outFileName, result.str());
            _exportBuffer.clear();
            result.clear();
        }
    }
}

void Reduce::resetMap()
{
    reduceMap.clear();
}

void Reduce::purgeBuffer(std::string fileName)
{
    exportz(fileName, true);
}

size_t Reduce::getExportBufferSize()
{
    return _exportBuffer.size();
}

/* The reduce class will have a method reduce() that will take a string with one key and an iterator of integers.
The reduce function should sum all the values in the iterator and then call an export() function (different from the Map class).
The export function will take two parameters, the key and resulting reduced value, and write the result out to the output directory.
Upon success an additional empty file SUCCESS will be written out to the output directory.
The reduce method itself should not directly deal with any File IO. */
