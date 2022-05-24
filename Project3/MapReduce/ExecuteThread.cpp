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

				std::thread createThread(thread, entry, _tempDir, pCreateObjectofMapPtr);
				createThread.join();
			}

		}
		catch (std::string ex) {
			utils.logMessage(ex + "\n");
			FreeLibrary(dll_handle);
		}
	}
	FreeLibrary(dll_handle);
}