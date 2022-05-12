///////////////////////////////////////////////////////////////////
//  ReduceTest.cpp -  Reduce Test Class                          //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 1                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                sleordan.@syr.edu                              //
//                jwashi05.@syr.edu                              //
///////////////////////////////////////////////////////////////////

#pragma once
#include "Test.h"
#include "../Header/FileManagement.h"

TEST(ReduceTest, TestReduce)
{
	std::string _unitTestOutDir = "./unitTestOutDir";

	//Test Exportz
	boost::filesystem::create_directory(_unitTestOutDir);

	FileManagement fm;

	std::string tmpFileName1 = _unitTestOutDir + "/testReduceFile1.txt";
	fm.createFile(_unitTestOutDir, tmpFileName1);

	/* Inserted the keys into the map data type*/
	/*Reduce r("testReduceFile1.txt", tmpFileName1);
	r.insertKey("i");
	r.insertKey("am");
	r.insertKey("but");
	r.insertKey("a");
	r.insertKey("humble");
	r.insertKey("developer");
	r.insertKey("i");
	r.insertKey("wish");
	r.insertKey("to");
	r.insertKey("continue");
	r.insertKey("striving");
	r.insertKey("for");
	r.insertKey("success");
	r.insertKey("success");
	r.insertKey("is");
	r.insertKey("important");
	r.insertKey("for");
	r.insertKey("developers");*/

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

	//r.exportz(tmpFileName1, true);

	//r.purgeBuffer("testReduceFile1.dat");

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
