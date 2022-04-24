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

	std::string _unitTestTmpDir = "./unitTestTempDir";

	//Test Setters Failure - empty path
	ASSERT_DEATH(fm.setInputDirectory(""), "");
	ASSERT_DEATH(fm.setOutputDirectory(""), "");
	ASSERT_DEATH(fm.setTempDirectory(""), "");

	//Test Setters Failure - invalid path
	ASSERT_DEATH(fm.setInputDirectory("invalidDir"), "");
	ASSERT_DEATH(fm.setOutputDirectory("invalidDir"), "");
	ASSERT_DEATH(fm.setTempDirectory("invalidDir"), "");
	
	boost::filesystem::create_directory(_unitTestTmpDir);

	//Test Setter/Getter Success
	fm.setInputDirectory(_unitTestTmpDir);
	ASSERT_EQ(_unitTestTmpDir, fm.getInputDirectory());

	fm.setOutputDirectory(_unitTestTmpDir);
	ASSERT_EQ(_unitTestTmpDir, fm.getOutputDirectory());

	fm.setTempDirectory(_unitTestTmpDir);
	ASSERT_EQ(_unitTestTmpDir, fm.getTempDirectory());

	boost::filesystem::remove_all(_unitTestTmpDir);
}

TEST(FileManagementTest, TestCreateFile)
{
	FileManagement fm;
	std::string _unitTestTmpDir = "./unitTestTempDir";
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
	boost::filesystem::create_directory(_unitTestTmpDir);
	std::string tmpFileName = _unitTestTmpDir + "/testCreateFile.dat";
	fm.createFile(_unitTestTmpDir, tmpFileName);
	ASSERT_TRUE(boost::filesystem::exists(tmpFileName));
	boost::filesystem::remove_all(_unitTestTmpDir);
}

TEST(FileManagementTest, TestWriteToFile)
{
	//Test Write File Success
	FileManagement fm;
	std::string _unitTestTmpDir = "./unitTestTempDir";
	std::string fileContentsWrite = "This is what I'd expect to see in the file.";
	boost::filesystem::create_directory(_unitTestTmpDir);
	std::string tmpFileName = _unitTestTmpDir + "/testWriteFile.dat";
	fm.createFile(_unitTestTmpDir, tmpFileName);
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
	boost::filesystem::remove_all(_unitTestTmpDir);
}

TEST(FileManagementTest, TestRemoveFile)
{
	//Test Remove File Success
	FileManagement fm;
	std::string _unitTestTmpDir = "./unitTestTempDir";
	boost::filesystem::create_directory(_unitTestTmpDir);
	std::string tmpFileName = _unitTestTmpDir + "/testRemoveFile.dat";
	fm.createFile(_unitTestTmpDir, tmpFileName);
	ASSERT_TRUE(boost::filesystem::exists(tmpFileName));
	fm.removeFile(tmpFileName);
	ASSERT_FALSE(boost::filesystem::exists(tmpFileName));
	boost::filesystem::remove_all(_unitTestTmpDir);
}

TEST(FileManagementTest, TestRetrieveInputFiles)
{
	//Test Retrieve Input Files Failure
	FileManagement fm;
	std::string _unitTestTmpDir = "./unitTestTempDir";

	boost::filesystem::create_directory(_unitTestTmpDir);
	std::string tmpFileName = _unitTestTmpDir;
	fm.setInputDirectory(_unitTestTmpDir);

	std::string tmpFileName1 = _unitTestTmpDir + "/testInputFileRetrieval1.dat";
	fm.createFile(_unitTestTmpDir, tmpFileName1);
	ASSERT_TRUE(boost::filesystem::exists(tmpFileName1));
	ASSERT_DEATH(fm.retrieveInputFiles(), "");

	std::string tmpFileName2 = _unitTestTmpDir + "/testInputFileRetrieval2.txt";
	fm.createFile(_unitTestTmpDir, tmpFileName2);
	ASSERT_TRUE(boost::filesystem::exists(tmpFileName2));
	ASSERT_DEATH(fm.retrieveInputFiles(), "");

	std::string fileContentsWrite = "I am but a humble developer. I wish to continue striving for success!. Success is important for developers.";
	fm.writeToFile(tmpFileName2, fileContentsWrite);
	fm.retrieveInputFiles();
	ASSERT_EQ(1, fm.getInputPathsSize());

	boost::filesystem::remove_all(_unitTestTmpDir);
}

TEST(FileManagementTest, TestExecuteFileMapping)
{
	FileManagement fm;
	std::string _unitTestTmpDir = "./unitTestTempDir";

	//create directories to use for test
	boost::filesystem::create_directory(_unitTestTmpDir);
	boost::filesystem::create_directory(_unitTestTmpDir + "/input");
	boost::filesystem::create_directory(_unitTestTmpDir + "/output");
	boost::filesystem::create_directory(_unitTestTmpDir + "/temp");

	//set directories
	std::string inputDirPath = _unitTestTmpDir + "/input";
	fm.setInputDirectory(inputDirPath);
	fm.setOutputDirectory(_unitTestTmpDir + "/output");
	fm.setTempDirectory(_unitTestTmpDir + "/temp");


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
	fm.writeToFile(tmpFileName1, fileContentsWrite);
	
	//run input retriveal
	fm.retrieveInputFiles();

	//execute mapping
	fm.executeFileMapping();

	//compare with output dir

	std::string expectedTempResult = "";
	expectedTempResult.append("(act,1)\n(i,1)\n(scene,1)\n(irousillonthe,1)\n(counts,1)\n(palace,1)\n(enter,1)\n(bertram,1)\n(the,1)\n");
	expectedTempResult.append("(countess,1)\n(of,1)\n(rousillon,1)\n(helena,1)\n(and,1)\n(lafeu,1)\n(all,1)\n(in,1)\n(black,1)\n(countess,1)\n");
	expectedTempResult.append("(in,1)\n(delivering,1)\n(my,1)\n(son,1)\n(from,1)\n(me,1)\n(i,1)\n(bury,1)\n(a,1)\n(second,1)\n(husband,1)\n(bertram,1)\n");
	expectedTempResult.append("(and,1)\n(i,1)\n(in,1)\n(going,1)\n(madam,1)\n(weep,1)\n(oer,1)\n(my,1)\n(fathers,1)\n(death,1)\n(anew,1)\n(but,1)\n(i,1)\n");
	expectedTempResult.append("(must,1)\n(attend,1)\n(his,1)\n(majestys,1)\n(command,1)\n(to,1)\n(whom,1)\n(i,1)\n(am,1)\n(now,1)\n(in,1)\n");
	expectedTempResult.append("(ward,1)\n(evermore,1)\n(in,1)\n(subjection,1)\n(lafeu,1)\n");

	for (auto const& entry : boost::filesystem::directory_iterator(_unitTestTmpDir + "/temp"))
	{
		if (boost::filesystem::is_regular_file(entry)) {

			std::string fileContentsRead = "";
			std::ifstream input(entry.path().string());
			std::stringstream fileContentsReadStream;

			while (input >> fileContentsReadStream.rdbuf()) {
				fileContentsRead.append(fileContentsReadStream.str());
			}
			fileContentsReadStream.clear();
			input.close();
			ASSERT_EQ(expectedTempResult, fileContentsRead);
		}
	}

	//cleanup
	boost::filesystem::remove_all(_unitTestTmpDir);
}
