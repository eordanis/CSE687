#ifndef __FILEMANAGEMENT_H_INCLUDED__
#define __FILEMANAGEMENT_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  FileManagement.h    -  header file for FileManagement class  //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  Project1, CSE687 SP22 - Object Oriented Design //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,}@syr.edu                            //
///////////////////////////////////////////////////////////////////

#pragma once
#include<string>
#include <boost/filesystem.hpp>
using namespace std;
class FileManagement
{
private: bool validate_dir_path(string path);
public:
	void set_input_dir_path(string path);
	void set_output_dir_path(string path);
	void set_temp_dir_path(string path);
	void get_all(boost::filesystem::path const& root, std::string const& ext);
};

#endif

/*
* File Management Class: This class should abstract away details of the file system.
* All file systems accesses should go through this class.
*/

