#pragma once
#ifdef REDUCEDLL_EXPORTS
#define REDUCELIBRARY_API __declspec(dllexport)
#else
#define REDUCELIBRARY_API __declspec(dllimport)
#endif


///////////////////////////////////////////////////////////////////
//  Reduce.h    -  header file for Reduce class					 //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 2                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,jwashi05}@syr.edu                    //
///////////////////////////////////////////////////////////////////

#include "IReduce.h"
#include <string>
#include <map>
#include <regex>

class Reduce : public IReduce
{
public:

	/*
	* Default Constructor for Reduce
	*/
	Reduce();

	/*
	* Default Deconstructor for Reduce
	*/
	virtual ~Reduce();

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

extern "C" {
	REDUCELIBRARY_API IReduce* _cdecl CreateObjectofReduce();
};
