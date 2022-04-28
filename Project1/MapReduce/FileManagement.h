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
//                {sleordan,jwashi05}@syr.edu                    //
///////////////////////////////////////////////////////////////////

#pragma once
#include <boost/filesystem.hpp>

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
	* Set the input directory to the passed string path
	* @param string input directory path
	*/
	void setInputDirectory(std::string);

	/*
	* Set the output directory to the passed string path
	* @param string output directory path
	*/
	void setOutputDirectory(std::string);

	/*
	* Set the temp directory to the passed string path
	* @param string temp directory path
	*/
	void setTempDirectory(std::string);

	/*
	* Return the input directory path
	* @return string input directory path
	*/
	std::string getInputDirectory();

	/*
	* Return the output directory path
	* @return string output directory path
	*/
	std::string getOutputDirectory();

	/*
	* Return the temp directory path
	* @return string temp directory path
	*/
	std::string getTempDirectory();

	/*
	* Retrieve all valid text files for input directory path
	*/
	void retrieveInputFiles();

	/*
	* Retrieve all valid text files for temp directory path
	*/
	void retrieveTempFiles();

	/*
	* Execute MapReduce process on each input file retrieved
	*/
	void executeFileMapping();

	/*
	* Execute Reduce process on each input file retrieved in Temp
	*/
	void executeReduce();

	/*
	* Create a file for passed file name if not already exists
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
	* Get current timestamp and generate a string representation
	* @return string with current timestamp
	*/
	std::string GetCurrentTimeForFileName();

	/*
	* Return size of input paths retrived
	*/
	size_t getInputPathsSize();

	/*
	* Return size of temp paths retrived
	*/
	size_t getTempPathsSize();

private: 
	
	/*
	* Validate the passed string directory path
	* @param string directory path
	*/
	bool validateDirPath(std::string);

	/*
	* Input directory path
	*/
	std::string _inputDir;

	/*
	* Output directory path
	*/
	std::string _outputDir;

	/*
	* Temp directory path
	*/
	std::string _tempDir;

	/*
	* Extension supported
	*/
	std::string _ext=".txt";

	/*
	* Extension supported
	*/
	std::string _dat = ".dat";

	/*
	* Extension supported for temporary files
	*/
	std::string _tmpExt = ".dat";

	/*
	* input file paths
	*/
	std::vector<boost::filesystem::path> _inputPaths;

	/*
	* temp file paths
	*/
	std::vector<boost::filesystem::path> _tempPaths;
};

#endif

/*
* File Management Class: This class should abstract away details of the file system.
* All file systems accesses should go through this class.
*/

