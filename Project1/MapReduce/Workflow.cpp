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

void Workflow::set_file_paths(std::string inputDirPath, std::string outputDirPath, std::string tempDirPath)
{
	FileManagement fm;

	//validate & set input directory path
	fm.setInputDirectory(inputDirPath);

	//validate & set output directory path
	fm.setOutputDirectory(outputDirPath);

	//validate & set temp directory path
	fm.setTempDirectory(tempDirPath);

}

void Workflow::execute_workflow()
{
	FileManagement fm;

	// get all valid files from passed input directory
	fm.get_all(fm.getInputDirectory(), ".txt");

	// start mapping of files found
	fm.execute_file_paths_iteration();

}
