///////////////////////////////////////////////////////////////////
//  Workflow.cpp -  - Workflow class that handles main           //
//                    buisiness logic                            //
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
#include "Workflow.h"
#include "FileManagement.h"

FileManagement fm;
MapReduceUtils utils;

//default Constructor
Workflow::Workflow() {
	
}

//default Deconstructor
Workflow::~Workflow() {

}

void Workflow::setDirectory(MapReduceUtils::DirectoryType directorytype, const std::string directoryPath)
{
	fm.setDirectory(directorytype, directoryPath);
}

void Workflow::execute_workflow()
{
	// get all valid files from input directory
	fm.retrieveDirectoryFiles(MapReduceUtils::DirectoryType::input);

	// start mapping of files found
	fm.executeFileMapping();

	// get all valid files from temp directory
	fm.retrieveDirectoryFiles(MapReduceUtils::DirectoryType::temp);

	// start reduce program
	fm.executeReduce();

}
