///////////////////////////////////////////////////////////////////
//  MapReduce.cpp -  - standalone command-line program that      //
//                    can run a word count MapReduce workflow    //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  Project1, CSE687 SP22 - Object Oriented Design //
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
	string title = "**************************************************    Map Reduce   ************************************************";
	string hl = "*******************************************************************************************************************";
	string usg = "This application is a standalone tool that will run a word count on text files in the user provided directory path.";
	cout << title << endl << usg << endl << hl << endl;
}
/*
* initialize input request and assignement
*/
void init_input()
{
	FileManagement fm;
	string ui;
	cout << "Please enter input file(s) directory path: ";
	getline(cin, ui);

	//validate & set input directory path
	fm.set_input_dir_path(ui);

	cout << "Please enter output file directory path: ";
	getline(cin, ui);

	//validate & set output directory path
	fm.set_output_dir_path(ui);

	cout << "Please enter temp file directory path: ";
	getline(cin, ui);

	//validate & set temp directory path
	fm.set_temp_dir_path(ui);
}

/*
* Exit the appliaction
*/
void finish() {
	cout << "MapReduce program has completed successfully. Now exiting. Goodbye!";
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
