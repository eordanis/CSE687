///////////////////////////////////////////////////////////////////
//  Threading.cpp   -  class file for Thread class               //
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
#include "Header/Threading.h"

void Threading::operator()(boost::filesystem::path entry, std::string _tempDir, CreateObjectofMap pCreateObjectofMapPtr)
{
	boost::filesystem::ifstream fileHandler(entry);
	std::string line;
	MapReduceUtils utils;

	//create tmp file for fileName, Map/Reduce/Sort will utilize this, with Reduce cleaning up
	std::string fileName = entry.stem().string();
	std::string tmpFileName = _tempDir;
	tmpFileName.append("\\").append(fileName).append(".dat");

	createFile(_tempDir, tmpFileName);

	IMap* map = pCreateObjectofMapPtr();
	map->setInputFileName(fileName);
	map->setTempFileName(tmpFileName);
	utils.logMessage("\tMapping file \"" + entry.filename().string() + "\"\n");
	while (getline(fileHandler, line)) {
		//pass file name and line to >> Map.map(filename, line)
		map->map(fileName, line);

	}
	fileHandler.close();
	delete map;
}

void Threading::createFile(std::string directory, std::string filePath)
{
	if (boost::filesystem::is_directory(directory)) {
		removeFile(filePath);
		std::ofstream output(filePath);
		output.close();
	}
}

void Threading::removeFile(std::string filePath)
{
	if (boost::filesystem::exists(filePath)) {
		boost::filesystem::remove(filePath);
	}
}