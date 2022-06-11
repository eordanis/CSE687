///////////////////////////////////////////////////////////////////
//  Threading.cpp   -  class file for Thread class               //
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
#include "Header/Threading.h"

void Threading::operator()(std::vector<boost::filesystem::path> bucketPaths, std::string tempDir, CreateObjectofMap pCreateObjectofMapPtr, std::string dirPath)
{
	MapReduceUtils utils;
	for (boost::filesystem::path entry : bucketPaths) {
		std::string sourceFileName = entry.stem().string();
		std::string sourceFilePath = dirPath;
		sourceFilePath.append("\\").append(sourceFileName).append(".txt");
		boost::filesystem::ifstream fileHandler(sourceFilePath);
		std::string line;
		
		//create tmp file for fileName, Map/Reduce/Sort will utilize this, with Reduce cleaning up
		
		std::string tempFilePath = tempDir;
		tempFilePath.append("\\").append(sourceFileName).append(".dat");

		createFile(tempDir, tempFilePath);

		IMap* map = pCreateObjectofMapPtr();
		map->setInputFileName(sourceFileName);
		map->setTempFileName(tempFilePath);
		utils.logMessage("\tMapping file \"" + entry.filename().string() + "\"\n");
		while (getline(fileHandler, line)) {
			//pass file name and line to >> Map.map(filename, line)
			map->map(sourceFileName, line);

		}
		fileHandler.close();
		delete map;
	}
}

void Threading::operator()(std::vector<boost::filesystem::path> bucketPaths, std::string outDir, CreateObjectofReduce pCreateObjectofReducePtr, std::string dirPath)
{
	MapReduceUtils utils;
	for (boost::filesystem::path entry : bucketPaths) {
		std::string sourceFileName = entry.stem().string();
		std::string sourceFilePath = dirPath;
		sourceFilePath.append("\\").append(sourceFileName).append(".dat");
		boost::filesystem::ifstream fileHandler(sourceFilePath);
		std::string line;
		std::string key;

		//create output file for dat files, Reduce will occur
		std::string outFilePath = outDir;
		outFilePath.append("\\").append(sourceFileName).append(".txt");
		createFile(outDir, outFilePath);

		IReduce* reduce = pCreateObjectofReducePtr();
		reduce->setTempFileName(sourceFileName);
		reduce->setOutputFileName(outFilePath);

		utils.logMessage("\tReducing file \"" + entry.filename().string() + "\"\n");

		reduce->resetMap();

		while (getline(fileHandler, line)) {
			key = reduce->getReduceData(line);

			if (!key.empty()) {
				reduce->insertKey(key);
			}
		}

		reduce->exportz(outDir + "/" + sourceFileName, false);

		//ensure we check the buffer to make sure it does not still have content
		if (reduce->getExportBufferSize() > 0) {
			reduce->purgeBuffer(outDir + "/" + sourceFileName);
		}

		fileHandler.close();
	}
}

void Threading::createFile(std::string directory, std::string filePath)
{
	if (boost::filesystem::is_directory(directory)) {
		removeFile(filePath);
		std::ofstream output(filePath);
		output.close();
	}
}

void Threading::removeFile(std::string filePath)
{
	if (boost::filesystem::exists(filePath)) {
		boost::filesystem::remove(filePath);
	}
}