#ifndef __FILEMANAGEMENTTEST_H_INCLUDED__
#define __FILEMANAGEMENTTEST_H_INCLUDED__
///////////////////////////////////////////////////////////////////
//  FileManagementTest.h    -  header file for                   //
//                             FileManagementTest class          //
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
#include "pch.h"

struct FileManagementTest : testing::Test
{
	FileManagement* _fm;
	FileManagementTest::FileManagementTest()
	{
		_fm = new FileManagement;
	}
	FileManagementTest::~FileManagementTest()
	{
	}
};

#endif
