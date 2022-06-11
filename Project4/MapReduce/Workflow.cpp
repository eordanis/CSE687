///////////////////////////////////////////////////////////////////
//  Workflow.cpp -  - Workflow class that handles main           //
//                    buisiness logic                            //
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
#include "./Header/Workflow.h"
#include "./Header/FileManagement.h"

FileManagement fm;

//default Constructor
Workflow::Workflow() {
	
}

//default Deconstructor
Workflow::~Workflow() {
	fm.~FileManagement();
}

void Workflow::setDirectory(MapReduceUtils::DirectoryType directorytype, const std::string directoryPath)
{
	fm.setDirectory(directorytype, directoryPath);
}

void Workflow::setThreadCount(const std::string threadCount)
{
	fm.setThreadCount(threadCount);
}

void Workflow::execute_workflow()
{
	/*
	* Partition valid input files into buckets per thread
	*/
	fm.startSocketServer();

	/*
	* Partition valid input files into buckets per thread
	*/
	fm.partitionInput();

	/*
	* stub process(thread) that runs mapper and when complete, broadcasts socket message indicating completion
	*/	
	fm.executeFileMapping();

	/*
	* stub process(thread) that listens for broadcast indicating mapper has successfully completed, then runs reducer
	*/
	fm.executeReduce();

}
