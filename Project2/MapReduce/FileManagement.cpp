///////////////////////////////////////////////////////////////////
//  FileManagement.cpp -  FileManagement Class                   //
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
#include "FileManagement.h"
#include "Map.h"
#include "Reduce.h"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iomanip>
#include <sstream>
#include <time.h>
#include <stdio.h>

FileManagement::FileManagement()
{
}

FileManagement::~FileManagement()
{
}

// Get + Set Methods for File Management Class
void FileManagement::setDirectory(MapReduceUtils::DirectoryType directoryType, const std::string dirPath) {
	if (validateDirPath(dirPath)) {
		switch (directoryType)
		{
		case MapReduceUtils::DirectoryType::input:
			_inputDir = dirPath; break;
		case MapReduceUtils::DirectoryType::output:
			_outputDir = dirPath; break;
		case MapReduceUtils::DirectoryType::temp:
			_tempDir = dirPath; break;
		default: MapReduceUtils utils;  utils.throwException("FileManagement:setDirectory", "Directory path undetermined."); break;
		}

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
	default:  MapReduceUtils utils;  utils.throwException("FileManagement:getDirectory", "Directory path undetermined."); break;
	}
}

// Files Management Methods
bool FileManagement::validateDirPath(std::string path)
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
	}
}

void FileManagement::retrieveDirectoryFiles(MapReduceUtils::DirectoryType directoryType)
{
	MapReduceUtils utils;

	std::string ext, type, dir;
	std::vector<boost::filesystem::path> *dirPath { nullptr };

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

	utils.logMessage("Executing File Mapping...\n");
	for (boost::filesystem::path entry : _inputPaths) {
		boost::filesystem::ifstream fileHandler(entry);
		std::string line;
		//create tmp file for fileName, Map/Reduce/Sort will utilize this, with Reduce cleaning up
		std::string fileName = entry.stem().string();
		std::string tmpFileName = _tempDir;
		tmpFileName.append("\\").append(fileName).append("_").append(getCurrentTimeForFileName()).append(_dat);
		createFile(_tempDir, tmpFileName);
		Map m;
		m.setInputFileName(fileName);
		m.setTempFileName(tmpFileName);
		utils.logMessage("\tMapping file \"" + entry.filename().string() + "\"\n");
		while (getline(fileHandler, line)) {
			//pass file name and line to >> Map.map(filename, line)
			m.map(fileName, line);

		}
		fileHandler.close();
		m.~Map();
	}
}

void FileManagement::executeReduce()
{
	MapReduceUtils utils;

	utils.logMessage("Executing File Reducing...\n");
	for (boost::filesystem::path entry : _tempPaths) {
		boost::filesystem::ifstream fileHandler(entry);
		std::string line;
		std::string key;

		//create output file for dat files, Reduce will occur
		std::string fileName = entry.stem().string();
		std::string outFileName = _outputDir;
		outFileName.append("\\").append(fileName).append("_").append(getCurrentTimeForFileName()).append(_txt);
		createFile(_outputDir, outFileName);

		Reduce r(fileName, outFileName);
		r.resetMap();
		utils.logMessage("\tReducing file \"" + entry.filename().string() + "\"\n");

		while (getline(fileHandler, line)) {
			key = r.getReduceData(line);

			if (!key.empty()) {
				r.insertKey(key);
			}
		}

		r.exportz(fileName, false);

		//ensure we check the buffer to make sure it does not still have content
		if (r.getExportBufferSize() > 0) {
			r.purgeBuffer(fileName);
		}

		fileHandler.close();
	}
}

void FileManagement::createFile(std::string directory, std::string filePath)
{
	if (boost::filesystem::is_directory(directory) && !boost::filesystem::exists(filePath)) {
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

std::string FileManagement::getCurrentTimeForFileName()
{
	const std::string& fmt = "%F_%T";
	std::tm bt{};
	std::time_t timer = time(0);
	localtime_s(&bt, &timer);
	char buf[64];
	std::string timestr = { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
	std::replace(timestr.begin(), timestr.end(), ':', '-');
	return timestr;
}
