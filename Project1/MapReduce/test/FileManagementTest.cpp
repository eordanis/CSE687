///////////////////////////////////////////////////////////////////
//  FileManagementTest.cpp -  FileManagement Test Class          //
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
#include "../FileManagement.h"
TEST(FileManagementTest, TestSetGetDirectory)
{
	FileManagement fm;

	//Test Setters Failure - empty path
	ASSERT_DEATH(fm.setInputDirectory(""), "");
	ASSERT_DEATH(fm.setOutputDirectory(""), "");
	ASSERT_DEATH(fm.setTempDirectory(""), "");

	//Test Setters Failure - invalid path
	ASSERT_DEATH(fm.setInputDirectory("invalidDir"), "");
	ASSERT_DEATH(fm.setOutputDirectory("invalidDir"), "");
	ASSERT_DEATH(fm.setTempDirectory("invalidDir"), "");
	

	//Test Setter/Getter Success
	fm.setInputDirectory("./");
	ASSERT_EQ("./", fm.getInputDirectory());

	fm.setOutputDirectory("./");
	ASSERT_EQ("./", fm.getOutputDirectory());

	fm.setTempDirectory("./");
	ASSERT_EQ("./", fm.getTempDirectory());
}

TEST(FileManagementTest, TestCreateFile)
{
	FileManagement fm;

	//Test Create File Fail
	fm.createFile("", "");
	ASSERT_FALSE(boost::filesystem::exists(""));
	fm.createFile("thisshouldfailhere", "");
	ASSERT_FALSE(boost::filesystem::exists(""));
	fm.createFile("", "thisshouldfailhere");
	ASSERT_FALSE(boost::filesystem::exists("thisshouldfailhere"));
	fm.createFile("thisshouldfailhere", "thisshouldfailhere");
	ASSERT_FALSE(boost::filesystem::exists("thisshouldfailhere"));

	//Test Create File Success
	std::string tmpFileName = "./testCreateFile.dat";
	fm.createFile("./", tmpFileName);
	ASSERT_TRUE(boost::filesystem::exists(tmpFileName));
	boost::filesystem::remove(tmpFileName);
}

TEST(FileManagementTest, TestWriteToFile)
{
	//Test Write File Success
	FileManagement fm;
	std::string fileContentsWrite = "This is what I'd expect to see in the file.";
	std::string tmpFileName = "./testWriteFile.dat";
	fm.createFile("./", tmpFileName);
	ASSERT_TRUE(boost::filesystem::exists(tmpFileName));
	fm.writeToFile(tmpFileName, fileContentsWrite);

	std::string fileContentsRead = "";
	std::ifstream input(tmpFileName);
	std::stringstream fileContentsReadStream;

	while (input >> fileContentsReadStream.rdbuf()) {
		fileContentsRead.append(fileContentsReadStream.str());
	}
	fileContentsReadStream.clear();
	input.close();
	ASSERT_EQ(fileContentsWrite, fileContentsRead);
	fm.removeFile(tmpFileName);
	ASSERT_FALSE(boost::filesystem::exists(tmpFileName));
}

TEST(FileManagementTest, TestRemoveFile)
{
	//Test Remove File Success
	FileManagement fm;
	std::string tmpFileName = "./testRemoveFile.dat";
	fm.createFile("./", tmpFileName);
	ASSERT_TRUE(boost::filesystem::exists(tmpFileName));
	fm.removeFile(tmpFileName);
	ASSERT_FALSE(boost::filesystem::exists(tmpFileName));
}

TEST(FileManagementTest, TestRetrieveInputFiles)
{
	//Test Retrieve Input Files Failure
	FileManagement fm;

	fm.setInputDirectory("./");


	std::string tmpFileName1 = "./testInputFileRetrieval1.dat";
	fm.removeFile(tmpFileName1);
	
	fm.createFile("./", tmpFileName1);
	ASSERT_TRUE(boost::filesystem::exists(tmpFileName1));
	ASSERT_DEATH(fm.retrieveInputFiles(), "");

	std::string tmpFileName2 = "./testInputFileRetrieval2.txt";
	fm.createFile("./", tmpFileName2);
	ASSERT_TRUE(boost::filesystem::exists(tmpFileName2));
	ASSERT_DEATH(fm.retrieveInputFiles(), "");

	std::string fileContentsWrite = "I am but a humble developer. I wish to continue striving for success!. Success is important for developers.";
	fm.writeToFile(tmpFileName2, fileContentsWrite);
	fm.retrieveInputFiles();
	ASSERT_EQ(1, fm.getInputPathsSize());

	fm.removeFile(tmpFileName1);
	ASSERT_FALSE(boost::filesystem::exists(tmpFileName1));
	fm.removeFile(tmpFileName2);
	ASSERT_FALSE(boost::filesystem::exists(tmpFileName2));
}

TEST(FileManagementTest, TestExecuteFileMapping)
{
	FileManagement fm;
}
