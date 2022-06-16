///////////////////////////////////////////////////////////////////
//  FileManagement.cpp -  FileManagement Class                   //
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
#include "./Header/FileManagement.h"
#include "./Header/ExecuteThread.h"
#include "./Header/Client.h"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iomanip>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <thread>

typedef IMap* (*CreateObjectofMap)();
typedef IReduce* (*CreateObjectofReduce)();
MapReduceUtils utils;

FileManagement::FileManagement()
{
}

FileManagement::~FileManagement()
{
}

// Get + Set Methods for File Management Class
void FileManagement::setDirectory(MapReduceUtils::DirectoryType directoryType, const std::string dirPath) {
	if (validateDirPath(directoryType, dirPath)) {
		switch (directoryType)
		{
		case MapReduceUtils::DirectoryType::input:
			_inputDir = dirPath; break;
		case MapReduceUtils::DirectoryType::output:
			_outputDir = dirPath; break;
		case MapReduceUtils::DirectoryType::temp:
			_tempDir = dirPath; break;
		case MapReduceUtils::DirectoryType::dll:
			_dllDir = dirPath; break;
		default: MapReduceUtils utils;  utils.throwException("FileManagement:setDirectory", "Directory path undetermined."); return;
		}
	}
}

void FileManagement::setThreadCount(const std::string threadCount)
{
	for (char const& c : threadCount) {
		if (std::isdigit(c) == 0) {
			utils.logMessage("Thread count provided \"" + threadCount + "\" does not contain all digits. Keeping default of 1 thread.");
			return;
		}
	}
	int tc = std::stoi(threadCount);
		if (tc > 1 && tc < 7) {
			_threads = tc;
		}
		else {
			utils.logMessage("Thread count provided \"" + threadCount + "\" must be greater than 1 and less than 7. Keeping default of 1 thread.");
		}
}

std::string FileManagement::getDirectory(MapReduceUtils::DirectoryType directoryType) {
	switch (directoryType)
	{
	case MapReduceUtils::DirectoryType::input:
		return _inputDir; break;
	case MapReduceUtils::DirectoryType::output:
		return _outputDir; break;
	case MapReduceUtils::DirectoryType::temp:
		return _tempDir; break;
	case MapReduceUtils::DirectoryType::dll:
		return _dllDir; break;
	default:  MapReduceUtils utils;  utils.throwException("FileManagement:getDirectory", "Directory path undetermined."); return "";
	}
}

// Files Management Methods
bool FileManagement::validateDirPath(MapReduceUtils::DirectoryType directoryType, std::string path)
{
	if (path.empty()) {
		utils.throwException("FileManagement:validateDirPath", "Path must not be empty.");
	}

	if (boost::starts_with(path, "\"")) {
		path.erase(path.begin());
	}

	if (boost::ends_with(path, "\"")) {
		path.erase(path.end() - 1);
	}

	if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path)) {

		//if dll directory, make sure MapDLL.dll and Reduce.dll exist
		if (MapReduceUtils::DirectoryType::dll == directoryType) {
			std::string missingDLL = "";
			if (!boost::filesystem::exists(path + "\\MapDLL.dll")) {
				missingDLL.append(" MapDLL.dll ");
			}

			if (missingDLL != "") {
				utils.throwException("FileManagement:validateDirPath", "Path provided \"" + path + "\" does not contain required dll:" + missingDLL);
			}
		}

		utils.logMessage("Path provided \"" + path + "\" is a valid directory path. Setting value.");
		return true;
	}
	else {
		utils.throwException("FileManagement:validateDirPath", "Path provided \"" + path + "\" is not a valid directory path.");
	}
	return false;
}

size_t FileManagement::getDirectoryPathsSize()
{
	return _fileCount;
}

void FileManagement::partitionInput()
{
	utils.logMessage("Partitioning Input File Workload...\n");
	std::vector<boost::filesystem::path> allValidInputs;
	if (boost::filesystem::exists(_inputDir) && boost::filesystem::is_directory(_inputDir))
	{
		for (auto const& entry : boost::filesystem::directory_iterator(_inputDir))
		{
			if (boost::filesystem::is_regular_file(entry) && entry.path().extension() == _txt && !boost::filesystem::is_empty(entry)) {
				boost::filesystem::path path = entry.path();
				path.replace_extension("");
				allValidInputs.emplace_back(path);
			}

		}
	}
	else
	{
		utils.throwException("FileManagement:retrieveDirectoryFiles", "Path provided \"" + _txt + "\" is not a valid directory.");
	}

	if (allValidInputs.size() == 0) {
		utils.throwException("FileManagement:retrieveDirectoryFiles", "Path provided \"" + _txt + "\" has no valid text files to map and reduce with extension.\"" + _txt + "\"");
	}
	int idealThreads = 3;
	_fileCount = allValidInputs.size();
	int threads = _threads <= _fileCount ? _threads : (idealThreads <= _fileCount ? idealThreads : 1);
	_threads = threads; //set threads to corrected threadCount
	int bucketSize = _fileCount / threads;
	int currentCount = 0;
	int currentThread = 1;
	std::vector<boost::filesystem::path> currentBucket;
	for (std::vector<boost::filesystem::path>::size_type i = 0; i != _fileCount; i++) {
		currentBucket.emplace_back(allValidInputs[i]); //fill the current bucket
		currentCount++;
		if ((currentThread != threads && currentCount > bucketSize) || (currentThread == threads && i == _fileCount - 1)) {
			currentCount = 0;
			currentThread++; //on to next thread
			//add bucket to partion holder
			_partitions.push_back(currentBucket);
			currentBucket.clear();
		}
	}
}

void FileManagement::executeFileMapping()
{
	// Check thread count
	HINSTANCE dll_handle = getDLLInformation(_dllDir, "\\MapDLL.dll");
	if (dll_handle) {
		ExecuteThread thread;
		std::thread mainThread(thread, dll_handle, _tempDir, _partitions, MapReduceUtils::OperationType::map, _threads, _inputDir);
		mainThread.join();
	}
	else {
		utils.throwException("FileManagement:executeFileMapping", "Cannot load MapDLL.dll");
	}
}

void FileManagement::executeReduce()
{
	HINSTANCE dll_handle = getDLLInformation(_dllDir, "\\ReduceDLL.dll");
	if (dll_handle) {
		ExecuteThread thread;
		std::thread mainThread(thread, dll_handle, _outputDir, _partitions, MapReduceUtils::OperationType::reduce, _threads, _tempDir);
		mainThread.join();
	}
	else {
		utils.throwException("FileManagement:executeReducec", "Cannot load ReduceDLL.dll");
	}
}

void FileManagement::createFile(std::string directory, std::string filePath)
{
	if (boost::filesystem::is_directory(directory)) {
		removeFile(filePath);
		std::ofstream output(filePath);
		output.close();
	}
}

void FileManagement::writeToFile(std::string filePath, std::string text)
{
	if (boost::filesystem::exists(filePath)) {
		std::fstream fs;
		fs.open(filePath, std::fstream::in | std::fstream::out | std::fstream::app);
		fs << text;
		fs.close();
	}
}

void FileManagement::removeFile(std::string filePath)
{
	if (boost::filesystem::exists(filePath)) {
		boost::filesystem::remove(filePath);
	}
}


HINSTANCE FileManagement::getDLLInformation(std::string _dllDir, std::string dllName) {

	std::string dllPath(_dllDir);
	dllPath.append(dllName);
	std::wstring soutput = std::wstring(dllPath.begin(), dllPath.end());

	LPCWSTR sw = soutput.c_str();
	return LoadLibrary(soutput.c_str());
}
