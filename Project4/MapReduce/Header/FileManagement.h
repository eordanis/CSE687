#ifndef __FILEMANAGEMENT_H_INCLUDED__
#define __FILEMANAGEMENT_H_INCLUDED__

///////////////////////////////////////////////////////////////////
//  FileManagement.h    -  header file for FileManagement class  //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 4                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,jwashi05}@syr.edu                    //
///////////////////////////////////////////////////////////////////

#pragma once
#include <boost/filesystem.hpp>
#include "MapReduceUtils.h"
#include "./IMap.h"
#include "./IReduce.h"

class FileManagement
{

public:

	/*
	* Default Constructor for FileManagement
	*/
	FileManagement();

	/*
	* Default Deconstructor for FileManagement
	*/
	~FileManagement();

	/*
	* Set the path for the indicated directory type 
	* @param DirectoryType indicates the type of directory to set path for
	* @param string directory path
	*/
	void setDirectory(MapReduceUtils::DirectoryType, const std::string);
	
	/*
	* Set thread count to inidcated value if valid, else keep default of 1
	* @param string representing thread count between 1 & 6
	*/
	void setThreadCount(const std::string);

	/*
	* Return the indicated directory type path
	* @param DirectoryType indicates the type of directory to retrieve path for
	* @return string directory path
	*/
	std::string getDirectory(MapReduceUtils::DirectoryType);

	/*
	* Return the indicated file valid file count size
	* @return size_t size of directory path
	*/
	size_t getDirectoryPathsSize();

	/*
	* Execute MapReduce process on each input file retrieved
	*/
	void executeFileMapping();

	/*
	* Execute Reduce process on each input file retrieved in Temp
	*/
	void executeReduce();

	/*
	*
	*/
	HINSTANCE getDLLInformation(std::string, std::string);

	/*
	* Create a file for passed file name if not already exists, if exists remove file then create fresh
	* @param string directory name
	* @param string filename
	*/
	void createFile(std::string, std::string);

	/*
	* Write passed string to file with file name if exists
	* @param string filename
	* @param string text value
	*/
	void writeToFile(std::string, std::string);

	/*
	* Remove file for passed file name if exists
	* @param string filename
	*/
	void removeFile(std::string tempFileName);

	/*
	* Partition input files into bucket chunks based off thread count
	*/
	void partitionInput();

private: 
	
	/*
	* Validate the passed string directory path
	* @param DirectoryType indicates the type of directory to validate
	* @param string directory path
	*/
	bool validateDirPath(MapReduceUtils::DirectoryType, std::string);

	/*
	* Input, output, and temp directory path
	*/
	std::string _inputDir, _outputDir, _tempDir, _dllDir;

	/*
	* Thread count indicator, defaults to 1
	*/
	int _threads = 1;

	/*
	* Holds total valid file count
	*/
	size_t _fileCount = 0;

	std::vector<std::vector<boost::filesystem::path>> _partitions;

	/*
	* Extension supported
	*/
	std::string _txt = ".txt";

	/*
	* Extension supported
	*/
	std::string _dat = ".dat";
};

#endif

/*
* File Management Class: This class should abstract away details of the file system.
* All file systems accesses should go through this class.
*/

