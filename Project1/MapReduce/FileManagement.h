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
private: bool validate_dir_path(std::string path);
public:
	/**
	* Set input directory path to passed string path if valid, else error is thrown.
	*
	* @param string path for input directory.
	*/
	void set_input_dir_path(std::string path);
	/**
	* Set output directory path to passed string path if valid, else error is thrown.
	*
	* @param string path for output directory.
	*/
	void set_output_dir_path(std::string path);
	/**
	* Set temp directory path to passed string path if valid, else error is thrown.
	*
	* @param string path for temp directory.
	*/
	void set_temp_dir_path(std::string path);
	/**
	* Gets and returns the path set for input directory.
	*
	* @return string path for input directory
	*/
	std::string get_input_dir_path();
	/**
	* Gets and returns the path set for output directory.
	*
	* @return string path for output directory
	*/
	std::string  get_output_dir_path();
	/**
	* Gets and returns the path set for temp directory.
	*
	* @return string path for temp directory
	*/
	std::string  get_temp_dir_path();
	/**
	* Gathers all valid input files at given path directory & extension.
	* If no valid files exist with extension at path, error is thrown.
	*
	* @param path value to gather files from.
	* @param ext extension type of files to gather.
	*/
	void get_all(boost::filesystem::path const& path, std::string const& ext);

	/*
	* Initiates collected file path iteration. 
	* Each file path collected is parsed, passing its file name and raw line of code to the Map.map function.
	*/
	void execute_file_paths_iteration();
};

#endif

/*
* File Management Class: This class should abstract away details of the file system.
* All file systems accesses should go through this class.
*/

