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
#include <math.h>
#include <thread>

void ExecuteThread::operator()(HINSTANCE dll_handle, std::string dir, std::vector<std::vector<boost::filesystem::path>> partitions, MapReduceUtils::OperationType operationType, int threadCount, std::string dirPath)
{
	if (MapReduceUtils::OperationType::map == operationType) {
		MapReduceUtils utils;
		CreateObjectofMap pCreateObjectofMapPtr = (CreateObjectofMap)GetProcAddress(HMODULE(dll_handle), "CreateObjectofMap");
		if (pCreateObjectofMapPtr) {
			try {
				Threading thread;
				utils.logMessage("Executing File Mapping...\n");
				std::vector<std::thread> vecOfThreads;
				for (int i = 0; i < threadCount; i++) {
					vecOfThreads.push_back(std::thread(thread, partitions[i], dir, pCreateObjectofMapPtr, dirPath)); //create thread and pass bucket over
				}
				// Iterate over the thread vector
				for (std::thread& th : vecOfThreads)
				{
					// If thread Object is Joinable then Join that thread.
					if (th.joinable()) {
						th.join();
					}
				}
			}
			catch (std::string ex) {
				utils.logMessage(ex + "\n");
				FreeLibrary(dll_handle);
			}
		}
	}
	else if (MapReduceUtils::OperationType::reduce == operationType) {
		MapReduceUtils utils;
		CreateObjectofReduce pCreateObjectofReducePtr = (CreateObjectofReduce)GetProcAddress(HMODULE(dll_handle), "CreateObjectofReduce");
		if (pCreateObjectofReducePtr) {
			try {
				Threading thread;
				utils.logMessage("Executing File Reducing...\n");
				std::vector<std::thread> vecOfThreads;
				for (int i = 0; i < threadCount; i++) {
					vecOfThreads.push_back(std::thread(thread, partitions[i], dir, pCreateObjectofReducePtr, dirPath)); //create thread and pass bucket over
				}
				// Iterate over the thread vector
				for (std::thread& th : vecOfThreads)
				{
					// If thread Object is Joinable then Join that thread.
					if (th.joinable()) {
						th.join();
					}
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