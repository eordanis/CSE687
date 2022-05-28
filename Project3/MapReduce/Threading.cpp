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

void Threading::operator()(boost::filesystem::path entry, std::string tempDir, CreateObjectofMap pCreateObjectofMapPtr)
{
	boost::filesystem::ifstream fileHandler(entry);
	std::string line;
	MapReduceUtils utils;

	//create tmp file for fileName, Map/Reduce/Sort will utilize this, with Reduce cleaning up
	std::string fileName = entry.stem().string();
	std::string tmpFileName = tempDir;
	tmpFileName.append("\\").append(fileName).append(".dat");

	createFile(tempDir, tmpFileName);

	IMap* map = pCreateObjectofMapPtr();
	map->setInputFileName(fileName);
	map->setTempFileName(tmpFileName);
	utils.logMessage("\tMapping file \"" + entry.filename().string() + "\"\n");
	while (getline(fileHandler, line)) {
		//pass file name and line to >> Map.map(filename, line)
		map->map(fileName, line);

	}
	fileHandler.close();
	delete map;
}

void Threading::operator()(boost::filesystem::path entry, std::string outDir, CreateObjectofReduce pCreateObjectofReducePtr)
{
	MapReduceUtils utils;
	boost::filesystem::ifstream fileHandler(entry);
	std::string line;
	std::string key;

	//create output file for dat files, Reduce will occur
	std::string fileName = entry.stem().string();
	std::string outFileName = outDir;
	outFileName.append("\\").append(fileName).append(".txt");
	createFile(outDir, outFileName);

	IReduce* reduce = pCreateObjectofReducePtr();
	reduce->setTempFileName(fileName);
	reduce->setOutputFileName(outFileName);

	utils.logMessage("\tReducing file \"" + entry.filename().string() + "\"\n");

	reduce->resetMap();

	while (getline(fileHandler, line)) {
		key = reduce->getReduceData(line);

		if (!key.empty()) {
			reduce->insertKey(key);
		}
	}

	reduce->exportz(outDir + "/" + fileName, false);

	//ensure we check the buffer to make sure it does not still have content
	if (reduce->getExportBufferSize() > 0) {
		reduce->purgeBuffer(outDir + "/" + fileName);
	}

	fileHandler.close();
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