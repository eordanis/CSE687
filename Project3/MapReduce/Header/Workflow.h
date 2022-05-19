
#ifndef __WORKFLOW_H_INCLUDED__
#define __WORKFLOW_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  Workflow.h    -  header file for Workflow class			     //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 3                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,jwashi05}@syr.edu                    //
///////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include "./MapReduceUtils.h"

class Workflow
{
public: 

	/*
	* Default Constructor for Workflow
	*/
	Workflow();

	/*
	* Default Deconstructor for Workflow
	*/
	~Workflow();

	/*
	* Set the path for the indicated directory type 
	* @param DirectoryType indicates the type of directory to set path for
	* @param string directory path
	*/
	void setDirectory(MapReduceUtils::DirectoryType, const std::string);

	/*
	* Executes workflow logic for MapReduce
	*/
	void execute_workflow();

};

#endif
