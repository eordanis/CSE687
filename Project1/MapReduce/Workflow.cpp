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
//                {sleordan,}@syr.edu                            //
///////////////////////////////////////////////////////////////////

#pragma once
#include "Workflow.h"
#include "FileManagement.h"

void Workflow::set_file_paths(std::string inputDirPath, std::string outputDirPath, std::string tempDirPath)
{
	FileManagement fm;

	//validate & set input directory path
	fm.set_input_dir_path(inputDirPath);

	//validate & set output directory path
	fm.set_output_dir_path(outputDirPath);

	//validate & set temp directory path
	fm.set_temp_dir_path(tempDirPath);

}

void Workflow::execute_workflow()
{
	FileManagement fm;

	// get all valid files from passed input directory
	fm.get_all(fm.get_input_dir_path(), ".txt");

	// start mapping of files found
	fm.execute_file_paths_iteration();

}
