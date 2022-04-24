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
#include "../FileManagement.h"

TEST(MapTest, TestBufferPurgeAndExport)
{
	std::string _unitTestTmpDir = "./unitTestTempDir";
	//Test Exportz
	boost::filesystem::create_directory(_unitTestTmpDir);

	FileManagement fm;

	std::string tmpFileName1 = _unitTestTmpDir + "/testExportFile1.txt";
	fm.createFile(_unitTestTmpDir, tmpFileName1);

	std::string tmpFileName2 = _unitTestTmpDir + "/testExportFile2.dat";
	fm.createFile(_unitTestTmpDir, tmpFileName2);

	std::string fileContentsWrite = "I am but a humble developer. I wish to continue striving for success!. Success is important for developers.";
	fm.writeToFile(tmpFileName1, fileContentsWrite);

	Map m("testExportFile1.txt", tmpFileName2);
	m.exportz("testExportFile1.txt", fileContentsWrite, false);

	ASSERT_TRUE(m.getExportBufferSize() != 0);
	ASSERT_TRUE(boost::filesystem::file_size(tmpFileName2) == 0);

	m.purgeBuffer("testExportFile2.dat");
	ASSERT_TRUE(m.getExportBufferSize() == 0);
	ASSERT_TRUE(boost::filesystem::file_size(tmpFileName2) != 0);

	boost::filesystem::remove_all(_unitTestTmpDir);
}

TEST(MapTest, TestMap)
{
	std::string _unitTestTmpDir = "./unitTestTempDir";
	//Test Exportz
	boost::filesystem::create_directory(_unitTestTmpDir);

	FileManagement fm;

	std::string tmpFileName1 = _unitTestTmpDir + "/testMapFile1.txt";
	fm.createFile(_unitTestTmpDir, tmpFileName1);

	std::string tmpFileName2 = _unitTestTmpDir + "/testMapFile2.dat";
	fm.createFile(_unitTestTmpDir, tmpFileName2);

	std::string fileContentsWrite = "I am but a humble developer. I wish to continue striving for success!. Success is important for developers.";
	fm.writeToFile(tmpFileName1, fileContentsWrite);

	Map m("testMapFile1.txt", tmpFileName2);
	m.map("testMapFile1.txt", fileContentsWrite);
	m.purgeBuffer("testMapFile2.dat");

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

