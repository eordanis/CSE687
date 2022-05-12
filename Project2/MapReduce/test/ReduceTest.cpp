///////////////////////////////////////////////////////////////////
//  ReduceTest.cpp -  Reduce Test Class                          //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 1                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                sleordan.@syreduce->edu                              //
//                jwashi05.@syreduce->edu                              //
///////////////////////////////////////////////////////////////////

#pragma once
#include "Test.h"
#include "../Header/IReduce.h"
#include "../Header/FileManagement.h"

typedef IReduce* (*CreateObjectofReduce)();

TEST(ReduceTest, TestReduce)
{
	std::string reduceDllPath("./ReduceDLL.dll");
	std::wstring stemp = std::wstring(reduceDllPath.begin(), reduceDllPath.end());

	LPCWSTR sw = stemp.c_str();
	HINSTANCE dll_handle = LoadLibrary(stemp.c_str());

	if (dll_handle) {
		CreateObjectofReduce pCreateObjectofReducePtr = (CreateObjectofReduce)GetProcAddress(HMODULE(dll_handle), "CreateObjectofReduce");
		if (pCreateObjectofReducePtr) {

			std::string _unitTestOutDir = "./unitTestOutDir";

			//Test Exportz
			boost::filesystem::create_directory(_unitTestOutDir);

			FileManagement fm;

			std::string tmpFileName1 = _unitTestOutDir + "/testReduceFile1.txt";
			fm.createFile(_unitTestOutDir, tmpFileName1);

			/* Inserted the keys into the map data type*/
			IReduce* reduce = pCreateObjectofReducePtr();
			reduce->setOutputFileName("testReduceFile1.txt");
			reduce->setTempFileName(tmpFileName1);

			reduce->insertKey("i");
			reduce->insertKey("am");
			reduce->insertKey("but");
			reduce->insertKey("a");
			reduce->insertKey("humble");
			reduce->insertKey("developer");
			reduce->insertKey("i");
			reduce->insertKey("wish");
			reduce->insertKey("to");
			reduce->insertKey("continue");
			reduce->insertKey("striving");
			reduce->insertKey("for");
			reduce->insertKey("success");
			reduce->insertKey("success");
			reduce->insertKey("is");
			reduce->insertKey("important");
			reduce->insertKey("for");
			reduce->insertKey("developers");

			/* Insert Data into testing file */
			std::string fileContentsWrite = "";
			fileContentsWrite.append("(a,1)\n");
			fileContentsWrite.append("(am,1)\n");
			fileContentsWrite.append("(but,1)\n");
			fileContentsWrite.append("(continue,1)\n");
			fileContentsWrite.append("(developer,1)\n");
			fileContentsWrite.append("(developers,1)\n");
			fileContentsWrite.append("(for,2)\n");
			fileContentsWrite.append("(humble,1)\n");
			fileContentsWrite.append("(i,2)\n");
			fileContentsWrite.append("(important,1)\n");
			fileContentsWrite.append("(is,1)\n");
			fileContentsWrite.append("(for,1)\n");
			fileContentsWrite.append("(striving,1)\n");
			fileContentsWrite.append("(success,2)\n");
			fileContentsWrite.append("(to,1)\n");
			fileContentsWrite.append("(wish,1)\n");

			/* Write to file */
			fm.writeToFile(tmpFileName1, fileContentsWrite);

			reduce->exportz(tmpFileName1, true);

			reduce->purgeBuffer("testReduceFile1.dat");

			std::string fileContentsRead = "";
			std::ifstream input(tmpFileName1);
			std::stringstream fileContentsReadStream;

			while (input >> fileContentsReadStream.rdbuf()) {
				fileContentsRead.append(fileContentsReadStream.str());
			}
			fileContentsReadStream.clear();
			input.close();

			ASSERT_EQ(fileContentsWrite, fileContentsRead);

			boost::filesystem::remove_all(_unitTestOutDir);
		}
	}
}
