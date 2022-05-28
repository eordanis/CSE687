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

void ExecuteThread::operator()(HINSTANCE dll_handle, std::string dir, std::vector<boost::filesystem::path> filePaths, MapReduceUtils::OperationType operationType)
{
	
	if (MapReduceUtils::OperationType::map == operationType) {
		Threading thread;
		MapReduceUtils utils;
		CreateObjectofMap pCreateObjectofMapPtr = (CreateObjectofMap)GetProcAddress(HMODULE(dll_handle), "CreateObjectofMap");
		if (pCreateObjectofMapPtr) {
			try {
				utils.logMessage("Executing File Mapping...\n");
				for (boost::filesystem::path entry : filePaths) {
					std::thread createThread(thread, entry, dir, pCreateObjectofMapPtr);
					createThread.join();
				}
			}
			catch (std::string ex) {
				utils.logMessage(ex + "\n");
				FreeLibrary(dll_handle);
			}
		}
	}
	else if (MapReduceUtils::OperationType::reduce == operationType) {
		Threading thread;
		MapReduceUtils utils;
		CreateObjectofReduce pCreateObjectofReducePtr = (CreateObjectofReduce)GetProcAddress(HMODULE(dll_handle), "CreateObjectofReduce");
		if (pCreateObjectofReducePtr) {
			try {
				utils.logMessage("Executing File Reducing...\n");
				for (boost::filesystem::path entry : filePaths) {
					std::thread createThread(thread, entry, dir, pCreateObjectofReducePtr);
					createThread.join();
				}
			}
			catch (std::string ex) {
				utils.logMessage(ex + "\n");
				FreeLibrary(dll_handle);
			}
		}
	}
	
	FreeLibrary(dll_handle);
}