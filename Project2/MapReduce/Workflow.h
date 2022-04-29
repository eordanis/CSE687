
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

	/*
	* Default Constructor for Workflow
	*/
	Workflow();

	/*
	* Default Deconstructor for Workflow
	*/
	~Workflow();

	/*
	* Set the input directory to the passed string path
	* @param string input directory path
	*/
	void setInputDirectory(std::string);

	/*
	* Set the output directory to the passed string path
	* @param string output directory path
	*/
	void setOutputDirectory(std::string);

	/*
	* Set the temp directory to the passed string path
	* @param string temp directory path
	*/
	void setTempDirectory(std::string);

	/*
	* Set the map dll to dll passed
	* @param string map dll path
	*/
	void setMapDLL(std::string);

	/*
	* Executes workflow logic for MapReduce
	*/
	void execute_workflow();

};

#endif
