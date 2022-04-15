#ifndef __FILEMANAGEMENT_H_INCLUDED__
#define __FILEMANAGEMENT_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  FileManagement.h    -  header file for FileManagement class  //
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
#include <boost/filesystem.hpp>

class FileManagement
{
private: 
	
	bool validate_dir_path(std::string);

	std::string _inputDir;

	std::string _outputDir;

	std::string _tempDir;

public:

	void setInputDirectory(std::string);

	void setOutputDirectory(std::string);

	void setTempDirectory(std::string);

	std::string getInputDirectory();

	std::string getOutputDirectory();

	std::string getTempDirectory();

	void get_all(boost::filesystem::path const&, std::string const&);

	void execute_file_paths_iteration();
};

#endif

/*
* File Management Class: This class should abstract away details of the file system.
* All file systems accesses should go through this class.
*/

