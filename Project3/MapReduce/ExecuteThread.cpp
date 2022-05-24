///////////////////////////////////////////////////////////////////
//  ExecuteThread.cpp   -  class file for Thread class           //
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
#include "./Header/ExecuteThread.h"
#include "./Header/Threading.h"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iomanip>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <thread>

void ExecuteThread::operator()(HINSTANCE dll_handle, std::string _tempDir, std::vector<boost::filesystem::path> _inputPaths)
{
	MapReduceUtils utils;
	Threading thread;

	CreateObjectofMap pCreateObjectofMapPtr = (CreateObjectofMap)GetProcAddress(HMODULE(dll_handle), "CreateObjectofMap");
	if (pCreateObjectofMapPtr) {
		try {
			utils.logMessage("Executing File Mapping...\n");
			for (boost::filesystem::path entry : _inputPaths) {

				//std::thread createThread(thread);
				boost::filesystem::ifstream fileHandler(entry);
				std::string line;

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

		}
		catch (std::string ex) {
			utils.logMessage(ex + "\n");
			FreeLibrary(dll_handle);
		}
	}
	FreeLibrary(dll_handle);
}

void ExecuteThread::createFile(std::string directory, std::string filePath)
{
	if (boost::filesystem::is_directory(directory)) {
		removeFile(filePath);
		std::ofstream output(filePath);
		output.close();
	}
}

void ExecuteThread::removeFile(std::string filePath)
{
	if (boost::filesystem::exists(filePath)) {
		boost::filesystem::remove(filePath);
	}
}