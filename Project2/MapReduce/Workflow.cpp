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

//default Constructor
Workflow::Workflow() {
	
}

//default Deconstructor
Workflow::~Workflow() {

}

void Workflow::setInputDirectory(std::string inputDirPath)
{
	//validate & set input directory path
	fm.setInputDirectory(inputDirPath);
}

void Workflow::setOutputDirectory(std::string outputDirPath)
{
	//validate & set output directory path
	fm.setOutputDirectory(outputDirPath);

}

void Workflow::setTempDirectory(std::string tempDirPath)
{
	//validate & set temp directory path
	fm.setTempDirectory(tempDirPath);
}

void Workflow::execute_workflow()
{
	// get all valid files from passed input directory
	fm.retrieveInputFiles();

	// start mapping of files found
	fm.executeFileMapping();

	// get all valid files from passed temp directory
	fm.retrieveTempFiles();

	// start reduce program
	fm.executeReduce();

}
