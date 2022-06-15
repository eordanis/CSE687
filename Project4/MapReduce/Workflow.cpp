///////////////////////////////////////////////////////////////////
//  Workflow.cpp -  - Workflow class that handles main           //
//                    buisiness logic                            //
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
#include "./Header/Workflow.h"
#include "./Header/FileManagement.h"
#include "Header/Client.h"
#include <windows.h>

FileManagement fm;

//default Constructor
Workflow::Workflow() {
	
}

//default Deconstructor
Workflow::~Workflow() {
	fm.~FileManagement();
}

void Workflow::setDirectory(MapReduceUtils::DirectoryType directorytype, const std::string directoryPath)
{
	fm.setDirectory(directorytype, directoryPath);
}

void Workflow::setThreadCount(const std::string threadCount)
{
	fm.setThreadCount(threadCount);
}

void Workflow::start_server() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    wchar_t  path[64] = { L"./Executables/Socket.exe" };
    bool ret = CreateProcess(
        L"Socket",          // No module name (use command line)
        path,          // Command line
        NULL,          // Process handle not inheritable
        NULL,          // Thread handle not inheritable
        false,         // Set handle inheritance to FALSE
        0,             // No creation flags
        NULL,          // Use parent's environment block
        NULL,          // Use parent's starting directory 
        &si,           // Pointer to STARTUPINFO structure
        &pi            // Pointer to PROCESS_INFORMATION structure
    );

    if (!ret) {
        printf("Error");
        abort();
    }

    //WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

}

void Workflow::execute_workflow()
{
	/*
	* Tell the Communication with the server
	*/
    //start_server();
	Client client(fm);
	client.Workflow();
}
