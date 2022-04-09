/********************************************************
* FileManagement.h -
* CSE687 SP22
* Stephanie Eordanidis & JT Washington
*********************************************************/
#ifndef __FILEMANAGEMENT_H_INCLUDED__
#define __FILEMANAGEMENT_H_INCLUDED__
#pragma once
#include<string>
using namespace std;
class FileManagement
{
private: bool validate_dir_path(string path);
public: void set_input_dir_path(string path);
public: void set_output_dir_path(string path);
public: void set_temp_dir_path(string path);
};

#endif

/*
* File Management Class: This class should abstract away details of the file system.
* All file systems accesses should go through this class.
*/

