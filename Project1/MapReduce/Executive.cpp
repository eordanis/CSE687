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
#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
	//we should add a new arg to determine if we want to run this
	//if (_RUN_TEST) {
		printf("Running main() from %s\n", __FILE__);
		testing::InitGoogleTest(&argc, argv);
		RUN_ALL_TESTS();
	//}
	

	// Print the opening message to the user
	introduction();

	Workflow workflow;

	if (argc < 7) {
		workflow.mapException("There are less than the required arguments for this command. Please verify arguments and try again");
	}
	
	if (argc > 7) {
		workflow.mapException("There are more than the required arguments for this command. Please verify arguments and try again");
	}

	if (!CheckFlag("-input", argc, argv)) {
		workflow.mapException("-input parameter cannot be found. Please verify arguments and try again");
	}
	if (!CheckFlag("-output", argc, argv)) {
		workflow.mapException("-output parameter cannot be found. Please verify arguments and try again");
	}
	if (!CheckFlag("-temp", argc, argv)) {
		workflow.mapException("-temp parameter cannot be found. Please verify arguments and try again");
	}

	for (int counter = 1; counter < argc; counter++)
	{
		if (counter + 1 != argc)
		{
			if (strcmp(argv[counter], "-input") == 0) 
			{
				workflow.setInputDirectory(argv[counter + 1]);
			}
			else if (strcmp(argv[counter], "-output") == 0)
			{
				workflow.setOutputDirectory(argv[counter + 1]);
			}
			else if (strcmp(argv[counter], "-temp") == 0)
			{
				workflow.setTempDirectory(argv[counter + 1]);
			}
		}
	}

	//start map reduce workflow
	workflow.execute_workflow();

	// end the program
	exitProgram();
}

// Print Message
void introduction()
{
	std::cout << "**************************************************    Map Reduce   ************************************************" << std::endl;
	std::cout << "*******************************************************************************************************************" << std::endl;
	std::cout << "This application is a standalone tool that will run a word count on text files in the user provided directory path." << std::endl;
	std::cout << "Expected Arguments:" << std::endl;
	std::cout << "\t-input <input path>\t\t: This is the path where the text files reside." << std::endl;
	std::cout << "\t-output <output path>\t\t: This is the path where the MapReduced result files will be placed." << std::endl;
	std::cout << "\t-temp <temp path>\t\t: This is the permitted temporary file location for MapReduce to utilize." << std::endl;
	std::cout << std::endl;
}

// Exit the appliaction
void exitProgram() {
	std::cout << "MapReduce program has completed successfully. Now exiting. Goodbye!";

	// EXIT_SUCCESS
	exit(0);
}

// Validate user input for expected flag
bool CheckFlag(std::string flag, int argc, char *argv[]) {

	for (int counter = 1; counter < argc; counter++)
	{
		if (counter + 1 != argc)
		{
			if (argv[counter] == flag) {

				return true;
			}
		}
	}

	return false;
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
