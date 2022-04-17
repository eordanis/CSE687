#ifndef __EXECUTIVE_H_INCLUDED__
#define __EXECUTIVE_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  Executive.h    -  header file for Main Program  //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 1                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                jwashi05@syr.edu                               //
///////////////////////////////////////////////////////////////////

#pragma once

/*
* Print introduction statement on start
*/
void introduction();

/*
* Exits the application
*/
void exitProgram();

/*
* Check user input for expected flags
* @param string 
* @param char* []
*/
bool CheckFlag(std::string, int, char*[]);

#endif