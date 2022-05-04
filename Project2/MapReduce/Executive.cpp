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
#include "MapReduceUtils.h"
#include "Workflow.h"
#include "Executive.h"
#include "gtest/gtest.h"
#include <windows.h>


int main(int argc, char* argv[])
{
	// New class instance that will handle MapReduc
	Workflow workflow;

	// Determine if test flag was included and validate args
	bool runUnitTests = validateArgs(argc, argv);

	// If the flag was added to run the test, proceed with test scripts, otherwise run program
	if (runUnitTests) {

		std::cout << std::endl << "******************************************    Running Map Reduce Unit Tests  ****************************************" << std::endl;
		std::cout << "*********************************************************************************************************************" << std::endl;
		testing::InitGoogleTest(&argc, argv);
		RUN_ALL_TESTS();

		std::cout << "*****************************************    Map Reduce Unit Tests Complete  ****************************************" << std::endl;
		std::cout << "*********************************************************************************************************************" << std::endl << std::endl;

	}
	else {
		// Print the usage statement to the user
		usageStatement();

		for (int counter = 1; counter < argc; counter++)
		{
			if (counter + 1 != argc)
			{
				if (strcmp(argv[counter], "-input") == 0)
				{
					workflow.setDirectory(MapReduceUtils::DirectoryType::input, argv[counter + 1]);
				}
				else if (strcmp(argv[counter], "-output") == 0)
				{
					workflow.setDirectory(MapReduceUtils::DirectoryType::output, argv[counter + 1]);
				}
				else if (strcmp(argv[counter], "-temp") == 0)
				{
					workflow.setDirectory(MapReduceUtils::DirectoryType::temp, argv[counter + 1]);
				}
				if (strcmp(argv[counter], "-mapDLL") == 0)
				{

					//TODO
				}
			}
		}
		/*
		* //PROF HELP!!!
		#ifdef MAPDLL_EXPORTS
			std::cout << "its defined"
		#endif
		HINSTANCE dll_handle = LoadLibrary(L"C:\\Users\\seord_000\\Documents\\GitHub\\CSE687\\Project2\\x64\\Debug\\MapDLL.dll");
		FARPROC func_addr;
		if (dll_handle) {
			std::cout << "Map Library Found" << std::endl;
			func_addr = GetProcAddress(HMODULE(dll_handle), "CreateObjectofMap");
			if (func_addr) {
				std::cout << "Map Constructor Found" << std::endl;
				typedef Map* (*PCreateObjectofMap)();
				PCreateObjectofMap pCreateObjectofMap =(PCreateObjectofMap)GetProcAddress(HMODULE(dll_handle), "CreateObjectofMap");
				Map* map = (pCreateObjectofMap)();

				func_addr = GetProcAddress(HMODULE(dll_handle), "map");
				if (func_addr) {
					std::cout << "Map Constructor Found" << std::endl;
					typedef void (Map::* Pmap)(std::string, std::string);
					PCreateObjectofMap pmap = <PCreateObjectofMap>(GetProcAddress(HMODULE(dll_handle), "map"));
					map->pmap();
				}
			}
			else {
				std::cout << "Map Function Not Found" << std::endl;
			}
		}
		else {
			std::cout << "Map Library Not Found" << std::endl;
		}
		FreeLibrary(dll_handle);
		exitProgram(); //just testing
		*/

		//start map reduce workflow
		workflow.execute_workflow();
	}

	// end the program
	exitProgram();
}



// Print Message
void usageStatement()
{
	std::cout << "**************************************************    Map Reduce   ************************************************" << std::endl;
	std::cout << "*******************************************************************************************************************" << std::endl;
	std::cout << "This application is a standalone tool that will run a word count on text files in the user provided directory path." << std::endl;
	std::cout << "\t*** NOTE: Files in temp & output path will be overwritten if files with like name are found. ***" << std::endl;
	std::cout << "Expected Arguments:" << std::endl;
	std::cout << "\t-input\t\t<input path>\t\t: This is the path where the text files reside." << std::endl;
	std::cout << "\t-output\t\t<output path>\t\t: This is the path where the MapReduced result files will be placed." << std::endl;
	std::cout << "\t-temp\t\t<temp path>\t\t: This is the permitted temporary file location for MapReduce to utilize." << std::endl;
	std::cout << "\t-mapDLL\t\t<mapDLL.dll path>\t: This is path to the mapDLL.dll file to use with program." << std::endl;
	std::cout << "Optional Arguments:" << std::endl;
	std::cout << "\t-rut\t\t\t\t\t: If this flag is present, tests will be run instead of application." << std::endl;
	std::cout << "\t-help\t\t\t\t\t: If this flag is present, usage statement will display and program will exit." << std::endl;
	std::cout << std::endl;
}

// Exit the appliaction
void exitProgram() {
	std::cout << "MapReduce program has completed successfully. Now exiting. Goodbye!";

	// EXIT_SUCCESS
	exit(0);
}

// Validate provided arguments and check to see if we are running tests
bool validateArgs(int argc, char* argv[]) {

	MapReduceUtils utils;
	int total = 9;
	bool runUnitTest = false;

	if (checkFlag("-rut", argc, argv)) {
		return true;
	}

	if (checkFlag("-help", argc, argv)) {
		// Print the usage statement to the user
		usageStatement();
		// end the program
		exitProgram();
	}

	if (argc < total) {
		utils.throwException("Executive:validateArgs", "There are less than the required arguments for this command.Please verify arguments and try again");
	}

	if (argc > total) {
		utils.throwException("Executive:validateArgs", "There are more than the required arguments for this command. Please verify arguments and try again");
	}

	if (!checkFlag("-input", argc, argv)) {
		utils.throwException("Executive:validateArgs", "-input parameter cannot be found. Please verify arguments and try again");
	}

	if (!checkFlag("-output", argc, argv)) {
		utils.throwException("Executive:validateArgs", "-output parameter cannot be found. Please verify arguments and try again");
	}

	if (!checkFlag("-temp", argc, argv)) {
		utils.throwException("Executive:validateArgs", "-temp parameter cannot be found. Please verify arguments and try again");
	}

	if (!checkFlag("-mapDLL", argc, argv)) {
		utils.throwException("Executive:validateArgs", "-temp parameter cannot be found. Please verify arguments and try again");
	}

	return false;
}

// Validate user input for expected flag
bool checkFlag(std::string flag, int argc, char* argv[]) {

	for (int counter = 0; counter < argc; counter++)
	{
		if (argv[counter] == flag) {
			return true;
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
