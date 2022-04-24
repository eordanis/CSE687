///////////////////////////////////////////////////////////////////
//  FileManagementTest.cpp -  FileManagement Test Class          //
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
#include "Test.h"
#include "../FileManagement.h"

TEST(FileManagementTest, TestSetDirectory)
{
	FileManagement fm;
	ASSERT_EXIT(fm.setInputDirectory(""), testing::ExitedWithCode(1), "FileManagement:validateDirPath:\tPath must not be empty.");
	ASSERT_EXIT(fm.setInputDirectory("test"), testing::ExitedWithCode(1), "FileManagement:get_all:\tPath provided \"test\" is not a valid directory.");
	ASSERT_EXIT(fm.setOutputDirectory(""), testing::ExitedWithCode(1), "FileManagement:validateDirPath:\tPath must not be empty.");
	ASSERT_EXIT(fm.setOutputDirectory("test"), testing::ExitedWithCode(1), "FileManagement:get_all:\tPath provided \"test\" is not a valid directory.");
	ASSERT_EXIT(fm.setTempDirectory(""), testing::ExitedWithCode(1), "FileManagement:validateDirPath:\tPath must not be empty.");
	ASSERT_EXIT(fm.setTempDirectory("test"), testing::ExitedWithCode(1), "FileManagement:get_all:\tPath provided \"test\" is not a valid directory.");
}