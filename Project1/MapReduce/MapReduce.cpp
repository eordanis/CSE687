/********************************************************
* MapReduce.cpp - standalone command-line program that
*                 can run a word count MapReduce workflow
* CSE687 SP22
* Stephanie Eordanidis & JT Washington
*********************************************************/

#pragma once
#include <iostream>
#include "FileManagement.h"
/*
* Function to print usage statement
*/
void usage()
{
	cout << "This application is a standalone tool that will run a word count \n on text files in the user provided directory path.\n\n";
}

/*
* Main function to drive program workflow
*/
int main()
{
	usage(); // print usage statement

	string ui;
	FileManagement fm;

	cout << "Please enter input file(s) directory path: ";
	getline(cin, ui);

	//validate & set input directory path
	fm.set_input_dir_path(ui);

	cout << "Please enter output file directory path: ";
	getline(cin, ui);

	//validate & set output directory path
	fm.set_output_dir_path(ui);

	cout << "Please enter output file directory path: ";
	getline(cin, ui);

	//validate & set temp directory path
	fm.set_temp_dir_path(ui);

	cout << "MapReduce program has completed successfull. Now exiting. Goodbye!";

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
