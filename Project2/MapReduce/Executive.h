#ifndef __EXECUTIVE_H_INCLUDED__
#define __EXECUTIVE_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  Executive.h    -  header file for Main Program  //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 2                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                jwashi05@syr.edu                               //
///////////////////////////////////////////////////////////////////

#pragma once

/*
* Print usage statement on start
*/
void usageStatement();

/*
* Exits the application
*/
void exitProgram();

/*
* Check user input for expected flags and return if we are running unit tests
* @param int
* @param char* []
* @return bool representation if we are to run unit test or not
*/
bool validateArgs(int, char* []);

/*
* Check user input for expected flags
* @param string
* @param int
* @param char* []
*/
bool checkFlag(std::string, int, char*[]);

#endif