///////////////////////////////////////////////////////////////////
//  FileManagement.cpp -  FileManagement Class                   //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 3                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,jwashi05}@syr.edu                    //
///////////////////////////////////////////////////////////////////

#pragma once
#include "./Header/FileManagement.h"
#include "./Header/ExecuteThread.h"
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
	MapReduceUtils utils;
	for (char const& c : threadCount) {
		if (std::isdigit(c) == 0) {
			utils.logMessage("Thread count provided \"" + threadCount + "\" does not contain all digits. Keeping default of 1 thread.");
			return;
		}
	}
	int tc = std::stoi(threadCount);
		if (tc > 1 && tc < 7) {
			_threadCount = tc;
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
	MapReduceUtils utils;
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
			//if (!boost::filesystem::exists(path + "\\ReduceDLL.dll")) {
			//	missingDLL.append(" ReduceDLL.dll ");
			//}
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

size_t FileManagement::getDirectoryPathsSize(MapReduceUtils::DirectoryType directoryType)
{
	if (MapReduceUtils::DirectoryType::input == directoryType) {
		return _inputPaths.size();

	}
	else if (MapReduceUtils::DirectoryType::temp == directoryType) {
		return _tempPaths.size();
	}
	else {
		MapReduceUtils utils;
		utils.throwException("FileManagement:retrieveDirectoryFiles", "Directory type undetermined.");
		return 0;
	}
}

void FileManagement::partitionFiles(MapReduceUtils::DirectoryType directoryType)
{

	/*
	* we need to figure out how we want to partition these.Depending on how this is done determines
	* how we rework the map/reduce calls. in theory we should be to tweak and thread the function calls themselves, 
	* just passing the thread # as a param and retrievingn files to map/reduce based off that
	* 
	* Ex.
	*  
		thread t1(executeFileMapping, 1);
		thread t2(executeFileMapping, 2);
		thread t3(executeFileMapping, 3);

		t1.join();
		t2.join();
		t3.join();

		//when done, can proceed to reduce functionallity
	*/ 
	MapReduceUtils utils;
	size_t pathSize = 0;
	if (MapReduceUtils::DirectoryType::input == directoryType) {
		pathSize = _inputPaths.size();

	}
	else if (MapReduceUtils::DirectoryType::temp == directoryType) {
		pathSize = _tempPaths.size();
	}
	else {
		utils.throwException("FileManagement:retrieveDirectoryFiles", "Directory type undetermined.");
	}

}

void FileManagement::retrieveDirectoryFiles(MapReduceUtils::DirectoryType directoryType)
{
	MapReduceUtils utils;

	std::string ext, type, dir;
	std::vector<boost::filesystem::path>* dirPath{ nullptr };

	if (MapReduceUtils::DirectoryType::input == directoryType) {
		ext = _txt;
		type = "input";
		dir = _inputDir;
		dirPath = &_inputPaths;

	}
	else if (MapReduceUtils::DirectoryType::temp == directoryType) {
		ext = _dat;
		type = "temp";
		dir = _tempDir;
		dirPath = &_tempPaths;
	}
	else {
		utils.throwException("FileManagement:retrieveDirectoryFiles", "Directory type undetermined.");
	}

	utils.logMessage("Searching for valid files at provided " + type + " path...\n");
	if (boost::filesystem::exists(dir) && boost::filesystem::is_directory(dir))
	{
		for (auto const& entry : boost::filesystem::directory_iterator(dir))
		{
			if (boost::filesystem::is_regular_file(entry) && entry.path().extension() == ext && !boost::filesystem::is_empty(entry)) {
				(*dirPath).emplace_back(entry.path());
			}

		}
	}
	else
	{
		utils.throwException("FileManagement:retrieveDirectoryFiles", "Path provided \"" + dir + "\" is not a valid directory.");
	}
	if ((*dirPath).size() == 0) {
		utils.throwException("FileManagement:retrieveDirectoryFiles", "Path provided \"" + dir + "\" has no valid text files to map and reduce with extension.\"" + ext + "\"");
	}
}

void FileManagement::executeFileMapping()
{
	MapReduceUtils utils;
	ExecuteThread thread;

	HINSTANCE dll_handle = getDLLInformation(_dllDir, "\\MapDLL.dll");

	if (dll_handle) {

		std::thread mainThread(thread, dll_handle, _tempDir, _inputPaths);
		mainThread.join();

	}
	else {
		utils.throwException("FileManagement:executeFileMapping", "Cannot load MapDLL.dll");
	}
}

void FileManagement::executeReduce()
{
	HINSTANCE dll_handle = getDLLInformation(_dllDir, "\\ReduceDLL.dll");
	MapReduceUtils utils;

	if (dll_handle) {
		CreateObjectofReduce pCreateObjectofReducePtr = (CreateObjectofReduce)GetProcAddress(HMODULE(dll_handle), "CreateObjectofReduce");
		if (pCreateObjectofReducePtr) {

			try {
				utils.logMessage("Executing File Reducing...\n");
				for (boost::filesystem::path entry : _tempPaths) {
					boost::filesystem::ifstream fileHandler(entry);
					std::string line;
					std::string key;

					//create output file for dat files, Reduce will occur
					std::string fileName = entry.stem().string();
					std::string outFileName = _outputDir;
					outFileName.append("\\").append(fileName).append(_txt);
					createFile(_outputDir, outFileName);

					IReduce* reduce = pCreateObjectofReducePtr();
					reduce->setTempFileName(fileName);
					reduce->setOutputFileName(outFileName);

					utils.logMessage("\tReducing file \"" + entry.filename().string() + "\"\n");

					reduce->resetMap();

					while (getline(fileHandler, line)) {
						key = reduce->getReduceData(line);

						if (!key.empty()) {
							reduce->insertKey(key);
						}
					}

					reduce->exportz(_outputDir + "/" + fileName, false);

					//ensure we check the buffer to make sure it does not still have content
					if (reduce->getExportBufferSize() > 0) {
						reduce->purgeBuffer(_outputDir + "/" + fileName);
					}

					fileHandler.close();

				}

			}
			catch (std::string ex) {

			}
		}
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
