///////////////////////////////////////////////////////////////////
//  Map.cpp -  Map Class                                         //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  Project1, CSE687 SP22 - Object Oriented Design //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,}@syr.edu                            //
///////////////////////////////////////////////////////////////////

#include "Map.h"

void Map::map()
{
}

void Map::exporter()
{
}

/* The map class will contain a public method map(), that accepts a key and value.
The key will be the file name and the value will be a single line of raw data from the file.
The map() function will tokenize the value into distinct words (remove punctuation, whitespace and capitalization).
The map() function will call a second function export that takes a key and value as two parameters.
The export function will buffer output in memory and periodically write the data out to disk (periodicity can be based on the size of the buffer).
The intermediate data will be written to the temporary directory (specified via command line). */
