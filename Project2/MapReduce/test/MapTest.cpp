///////////////////////////////////////////////////////////////////
//  MapTest.cpp -  Map Test Class                                //
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
#include "../Map.h"

TEST(MapTest, TestMap)
{
	std::string _unitTestTmpDir = "./unitTestTempDir";
	//Test Exportz
	boost::filesystem::create_directory(_unitTestTmpDir);

	std::string tmpFileName1 = _unitTestTmpDir + "/testMapFile1.txt";
	std::ofstream output1(tmpFileName1);
	output1.close();

	std::string tmpFileName2 = _unitTestTmpDir + "/testMapFile2.dat";
	std::ofstream output2(tmpFileName2);
	output2.close();

	std::string fileContentsWrite = "I am but a humble developer. I wish to continue striving for success!. Success is important for developers.";
	std::fstream fs;
	fs.open(tmpFileName1, std::fstream::in | std::fstream::out | std::fstream::app);
	fs << fileContentsWrite;
	fs.close();

	Map m;
	m.setInputFileName("testMapFile1.txt");
	m.setTempFileName(tmpFileName2);
	m.map("testMapFile1.txt", fileContentsWrite);
	m.~Map();

	std::string expectedTempResults = "";
	expectedTempResults.append("(i,1)\n");
	expectedTempResults.append("(am,1)\n");
	expectedTempResults.append("(but,1)\n");
	expectedTempResults.append("(a,1)\n");
	expectedTempResults.append("(humble,1)\n");
	expectedTempResults.append("(developer,1)\n");
	expectedTempResults.append("(i,1)\n");
	expectedTempResults.append("(wish,1)\n");
	expectedTempResults.append("(to,1)\n");
	expectedTempResults.append("(continue,1)\n");
	expectedTempResults.append("(striving,1)\n");
	expectedTempResults.append("(for,1)\n");
	expectedTempResults.append("(success,1)\n");
	expectedTempResults.append("(success,1)\n");
	expectedTempResults.append("(is,1)\n");
	expectedTempResults.append("(important,1)\n");
	expectedTempResults.append("(for,1)\n");
	expectedTempResults.append("(developers,1)\n");

	std::string fileContentsRead = "";
	std::ifstream input(tmpFileName2);
	std::stringstream fileContentsReadStream;

	while (input >> fileContentsReadStream.rdbuf()) {
		fileContentsRead.append(fileContentsReadStream.str());
	}
	fileContentsReadStream.clear();
	input.close();
	ASSERT_EQ(expectedTempResults, fileContentsRead);

	boost::filesystem::remove_all(_unitTestTmpDir);
}

