#ifndef __REDUCE_H_INCLUDED__
#define __REDUCE_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  Reduce.h    -  header file for Reduce class                  //
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
#include<string>  
#include<iterator>
#include<vector>
#include <map>

class Reduce
{
public:
	/*
	* Default Constructor for Reduce
	*/
	Reduce();

	/*
	* Default Deconstructor for Reduce
	*/
	~Reduce();

	/*
	* Parameterized Constructor for Reduce
	* @param string filename of source file
	* @param string outFileName of temporary file created
	*/
	Reduce(std::string, std::string);

	/*
	* 
	*/
	void reduce(std::string key, std::vector<int>::iterator counts);

	/*
	*
	*/
	std::string getReduceData(std::string);

	/*
	*
	*/
	void insertKey(std::string);

	/*
	* Purge the export buffer of any remaining values
	* @param fileName to purge buffer for
	*/
	void purgeBuffer(std::string);

	/*
	* Return the current size of the export buffer
	*/
	size_t getExportBufferSize();

	/*
	* 
	*/
	void exportz(std::string, bool);

	/*
	*
	*/
	void resetMap();

private:

	/**
	 * Max size of export buffer
	 */
	int _exportBufferMaxSize = 50;

	/**
	 * Map holding string filename key and vector buffer
	 */
	std::vector<std::string> _exportBuffer;


	/**
	* Map to hold the data for Reduce
	*/
	std::map<std::string, int> reduceMap;

	/**
	* Strings representing the map instance's temporary file name and source text file name
	*/
	std::string _outFileName, _fileName;
};
#endif

