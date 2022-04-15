///////////////////////////////////////////////////////////////////
//  Executive.cpp -  - standalone command-line program that      //
//                    can run a word count MapReduce workflow    //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 1                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                sleordan.@syr.edu                              //
//                jwashi05.@syr.edu                              //
///////////////////////////////////////////////////////////////////

#pragma once
#include <iostream>
#include "Workflow.h"
#include "Executive.h"
using std::cout;
using std::cin;
using std::string;

int main(int argc, char* argv[])
{
	Workflow workflow;

	if (argc < 7) {

		workflow.MapException("There are less than the required arguments for this command. Please update and try again");
	}
	else if (argc > 7) {
		workflow.MapException("There are more than the required arguments for this command. Please update and try again");
	}
	else {
		for (int counter = 1; counter < argc; counter++)
		{
			if (counter + 1 != argc)
			{
				if (strcmp(argv[counter], "-input") == 0) {

					workflow.SetInputFilePath(argv[counter + 1]);
				}
				else if (strcmp(argv[counter], "-output") == 0)
				{
					workflow.SetOutputFilePath(argv[counter + 1]);
				}
				else if (strcmp(argv[counter], "-temp") == 0)
				{
					workflow.SetTempFilePath(argv[counter + 1]);
				}
			}
		}
	}

	// Print the opening message to the user
	Introduction();

	//start map reduce workflow
	workflow.execute_workflow();

	// end the program
	ExitProgram();
}

// Print Message
void Introduction()
{
	cout << "**************************************************    Map Reduce   ************************************************\n";
	cout << "*******************************************************************************************************************\n";
	cout << "This application is a standalone tool that will run a word count on text files in the user provided directory path.\n";
}

// Exit the appliaction
void ExitProgram() {
	cout << "MapReduce program has completed successfully. Now exiting. Goodbye!";

	// EXIT_SUCCESS
	exit(0);
}

/*
*
* Technical Requirements
*
* 1)	Your program will accept three inputs via command-line:
*
*    a)	Directory that holds input files.
*    b)	Directory to hold output files.
*    c)	Temporary directory to hold intermediate output files.
*
* 2)	Code will include the following classes, see below for discussion of how they should work.
*    a)	Map: Is given data from a file (does not parse the file itself) and outputs a separate temporary file that holds (word, 1) for each occurrence of every word.
*    b)	Reduce: Is given sorted data from the intermediate file and reduces the results by aggregating the values.
*    c)	Workflow: Executes the main business logic.
*    d)	Executive: Contains the main function and any additional utility functions/data required.
*
*/
