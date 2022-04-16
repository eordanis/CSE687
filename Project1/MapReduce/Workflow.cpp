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
#include <iostream>
#include "Workflow.h"
#include "FileManagement.h"
#include <boost/log/trivial.hpp>
using std::string;

FileManagement fm;

//default Constructor
Workflow::Workflow() {
	
}

void Workflow::SetInputFilePath(string inputDirPath)
{
	//validate & set input directory path
	fm.setInputDirectory(inputDirPath);
}

void Workflow::SetOutputFilePath(string outputDirPath)
{
	//validate & set output directory path
	fm.setOutputDirectory(outputDirPath);

}

void Workflow::SetTempFilePath(string tempDirPath)
{
	//validate & set temp directory path
	fm.setTempDirectory(tempDirPath);
}

void Workflow::execute_workflow()
{
	// get all valid files from passed input directory
	fm.get_all(fm.getInputDirectory(), ".txt");

	// start mapping of files found
	fm.execute_file_paths_iteration();

}

void Workflow::MapException(string exception) {

	BOOST_LOG_TRIVIAL(error) << "Workflow:  " << exception;
	exit(1);
}
