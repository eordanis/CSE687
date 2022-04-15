
#ifndef __WORKFLOW_H_INCLUDED__
#define __WORKFLOW_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  Workflow.h    -  header file for Workflow class			     //
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

class Workflow
{
public: 
	/**
	* Set passed directory path passed string paths if valid, else error is thrown.
	*
	* @param inputDirPath - string path for input directory.
	* @param outputDirPath - string path for output directory.
	* @param tempDirPath - string path for temp directory.
	*/
	void set_file_paths(std::string inputDirPath, std::string outputDirPath, std::string tempDirPath);

	/**
	* Initialize workflow procedure
	*/
	void execute_workflow();
};

#endif
