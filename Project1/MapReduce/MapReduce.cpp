///////////////////////////////////////////////////////////////////
//  MapReduce.cpp -  - standalone command-line program that      //
//                    can run a word count MapReduce workflow    //
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
#include <iostream>
#include "FileManagement.h"

/*
* Print usage statement
*/
void usage()
{
	std::string title = "**************************************************    Map Reduce   ************************************************";
	std::string hl = "*******************************************************************************************************************";
	std::string usg = "This application is a standalone tool that will run a word count on text files in the user provided directory path.";
	std::cout << title << std::endl << usg << std::endl << hl << std::endl;
}
/*
* initialize input request and assignement
*/
void init_input()
{
	FileManagement fm;
	std::string ui;
	std::cout << "Please enter input file(s) directory path: ";
	std::getline(std::cin, ui);

	//validate & set input directory path
	fm.set_input_dir_path(ui);

	std::cout << "Please enter output file directory path: ";
	std::getline(std::cin, ui);

	//validate & set output directory path
	fm.set_output_dir_path(ui);

	std::cout << "Please enter temp file directory path: ";
	std::getline(std::cin, ui);

	//validate & set temp directory path
	fm.set_temp_dir_path(ui);

	//check & get all valid files at given input path
	fm.get_all(fm.get_input_dir_path(), ".txt");

	//begin MapReduce on collected file paths
	fm.execute_file_paths_iteration();
}

/*
* Exit the appliaction
*/
void finish() {
	std::cout << "MapReduce program has completed successfully. Now exiting. Goodbye!";
	// EXIT_SUCCESS
	exit(0);
}

/*
* Main function to drive program workflow
*/
int main()
{
	usage();		// print usage statement
	init_input();	// request user input and set values
	finish();		// end the program
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
