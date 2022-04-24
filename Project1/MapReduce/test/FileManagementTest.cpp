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

std::string _tmpDir = "./unitTestTempDir";
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
	
	boost::filesystem::create_directory(_tmpDir);

	//Test Setter/Getter Success
	fm.setInputDirectory(_tmpDir);
	ASSERT_EQ(_tmpDir, fm.getInputDirectory());

	fm.setOutputDirectory(_tmpDir);
	ASSERT_EQ(_tmpDir, fm.getOutputDirectory());

	fm.setTempDirectory(_tmpDir);
	ASSERT_EQ(_tmpDir, fm.getTempDirectory());

	boost::filesystem::remove_all(_tmpDir);
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
	boost::filesystem::create_directory(_tmpDir);
	std::string tmpFileName = _tmpDir + "/testCreateFile.dat";
	fm.createFile(_tmpDir, tmpFileName);
	ASSERT_TRUE(boost::filesystem::exists(tmpFileName));
	boost::filesystem::remove_all(_tmpDir);
}

TEST(FileManagementTest, TestWriteToFile)
{
	//Test Write File Success
	FileManagement fm;
	std::string fileContentsWrite = "This is what I'd expect to see in the file.";
	boost::filesystem::create_directory(_tmpDir);
	std::string tmpFileName = _tmpDir + "/testWriteFile.dat";
	fm.createFile(_tmpDir, tmpFileName);
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
	boost::filesystem::remove_all(_tmpDir);
}

TEST(FileManagementTest, TestRemoveFile)
{
	//Test Remove File Success
	FileManagement fm;
	boost::filesystem::create_directory(_tmpDir);
	std::string tmpFileName = _tmpDir + "/testRemoveFile.dat";
	fm.createFile(_tmpDir, tmpFileName);
	ASSERT_TRUE(boost::filesystem::exists(tmpFileName));
	fm.removeFile(tmpFileName);
	ASSERT_FALSE(boost::filesystem::exists(tmpFileName));
	boost::filesystem::remove_all(_tmpDir);
}

TEST(FileManagementTest, TestRetrieveInputFiles)
{
	//Test Retrieve Input Files Failure
	FileManagement fm;

	boost::filesystem::create_directory(_tmpDir);
	std::string tmpFileName = _tmpDir;
	fm.setInputDirectory(_tmpDir);

	std::string tmpFileName1 = _tmpDir + "/testInputFileRetrieval1.dat";
	fm.createFile(_tmpDir, tmpFileName1);
	ASSERT_TRUE(boost::filesystem::exists(tmpFileName1));
	ASSERT_DEATH(fm.retrieveInputFiles(), "");

	std::string tmpFileName2 = _tmpDir + "/testInputFileRetrieval2.txt";
	fm.createFile(_tmpDir, tmpFileName2);
	ASSERT_TRUE(boost::filesystem::exists(tmpFileName2));
	ASSERT_DEATH(fm.retrieveInputFiles(), "");

	std::string fileContentsWrite = "I am but a humble developer. I wish to continue striving for success!. Success is important for developers.";
	fm.writeToFile(tmpFileName2, fileContentsWrite);
	fm.retrieveInputFiles();
	ASSERT_EQ(1, fm.getInputPathsSize());

	boost::filesystem::remove_all(_tmpDir);
}

TEST(FileManagementTest, TestExecuteFileMapping)
{
	FileManagement fm;

	//create directories to use for test
	boost::filesystem::create_directory(_tmpDir);
	boost::filesystem::create_directory(_tmpDir + "/input");
	boost::filesystem::create_directory(_tmpDir + "/output");
	boost::filesystem::create_directory(_tmpDir + "/temp");

	//set directories
	std::string inputDirPath = _tmpDir + "/input";
	fm.setInputDirectory(inputDirPath);
	fm.setOutputDirectory(_tmpDir + "/output");
	fm.setTempDirectory(_tmpDir + "/temp");


	//create a text files with content under input
	std::string tmpFileName1 = inputDirPath + "/testMapExecution1.txt";
	fm.createFile(inputDirPath, tmpFileName1);

	std::string fileContentsWrite = "";
	fileContentsWrite.append("ACT I\n");
	fileContentsWrite.append("SCENE I.Rousillon.The COUNT's palace.\n");
	fileContentsWrite.append("\n");
	fileContentsWrite.append("Enter BERTRAM, the COUNTESS of Rousillon, HELENA, and LAFEU, all in black\n");
	fileContentsWrite.append("COUNTESS\n");
	fileContentsWrite.append("In delivering my son from me, I bury a second husband.\n");
	fileContentsWrite.append("BERTRAM\n");
	fileContentsWrite.append("And I in going, madam, weep o'er my father's death\n");
	fileContentsWrite.append("anew : but I must attend his majesty's command, to\n");
	fileContentsWrite.append("whom I am now in ward, evermore in subjection.\n");
	fileContentsWrite.append("LAFEU\n");
	fileContentsWrite.append("You shall find of the king a husband, madam; you, \n");
	fileContentsWrite.append("sir, a father : he that so generally is at all times\n");
	fileContentsWrite.append("good must of necessity hold his virtue to you; whose\n");
	fileContentsWrite.append("worthiness would stir it up where it wanted rather\n");
	fileContentsWrite.append("than lack it where there is such abundance.\n");
	fileContentsWrite.append("COUNTESS\n");
	fileContentsWrite.append("What hope is there of his majesty's amendment?\n");
	fileContentsWrite.append("LAFEU\n");
	fileContentsWrite.append("He hath abandoned his physicians, madam; under whose\n");
	fileContentsWrite.append("practises he hath persecuted time with hope, and \n");
	fileContentsWrite.append("finds no other advantage in the process but only the\n");
	fileContentsWrite.append("losing of hope by time.\n");
	fileContentsWrite.append("COUNTESS\n");
	fileContentsWrite.append("This young gentlewoman had a father, --O, that\n");
	fileContentsWrite.append("'had'!how sad a passage 'tis!--whose skill was\n");
	fileContentsWrite.append("almost as great as his honesty; had it stretched so\n");
	fileContentsWrite.append("far, would have made nature immortal, and death\n");
	fileContentsWrite.append("should have play for lack of work.Would, for the\n");
	fileContentsWrite.append("king's sake, he were living! I think it would be\n");
	fileContentsWrite.append("the death of the king's disease.\n");
	fileContentsWrite.append("LAFEU");
	fm.writeToFile(tmpFileName1, fileContentsWrite);
	
	//run input retriveal
	fm.retrieveInputFiles();

	//execute mapping
	fm.executeFileMapping();

	//compare with output dir

	//cleanup
	boost::filesystem::remove_all(_tmpDir);
}
