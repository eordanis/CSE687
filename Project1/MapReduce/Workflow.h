
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
using std::string;

class Workflow
{
public: 

	Workflow();

	void SetInputFilePath(string);

	void SetOutputFilePath(string);

	void SetTempFilePath(string);

	void execute_workflow();

	void MapException(string);
};

#endif
