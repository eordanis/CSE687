#ifndef __MAPREDUCEUTILS_H_INCLUDED__
#define __MAPREDUCEUTILS_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  MapReduceUtils.h    -  header file for MapReduceUtils        //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 3                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                jwashi05@syr.edu                               //
///////////////////////////////////////////////////////////////////

#pragma once
#include <string>

class MapReduceUtils
{
public:
	/*
	* Default Constructor for MapReduceUtils
	*/
	MapReduceUtils();

	/*
	* Default Deconstructor for MapReduceUtils
	*/
	~MapReduceUtils();

	/*
	* Throws an error for the passed parameters and exits with exit code 1
	* @param string method - caller class name and method
	* @param string exception
	*/
	void throwException(std::string, std::string);

	/*
	* Log passed message
	* @param string msg - message to log
	*/
	void logMessage(std::string msg);

	/*
	* Enumeration object to determine directory type to work on
	*/
	const enum DirectoryType
	{
		input,
		output,
		temp,
		dll,
		threads
	};

	/*
	* Enumeration object to determine operation type to work on
	*/
	const enum OperationType
	{
		map,
		reduce
	};
};

#endif
