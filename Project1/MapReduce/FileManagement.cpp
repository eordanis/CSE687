///////////////////////////////////////////////////////////////////
//  FileManagement.cpp -  FileManagement Class                   //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 1                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,jwashi05}@syr.edu                    //
///////////////////////////////////////////////////////////////////

#pragma once
#include "FileManagement.h"
#include "Map.h"
#include "MapReduceUtils.h"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem/fstream.hpp>
#include <iomanip>
#include <sstream>
#include <time.h>
#include <stdio.h>

FileManagement::FileManagement()
{
}

FileManagement::~FileManagement()
{
}

// Get + Set Methods for File Management Class
void FileManagement::setInputDirectory(std::string inputDir) {
    if (validateDirPath(inputDir)) {
        _inputDir = inputDir;
    }
}
std::string FileManagement::getInputDirectory() {
    return _inputDir;

}

void FileManagement::setOutputDirectory(std::string outputDir) {
    if (validateDirPath(outputDir)) {
        _outputDir = outputDir;
    }
}
std::string FileManagement::getOutputDirectory() {
    return _outputDir;

}

void FileManagement::setTempDirectory(std::string tempDir) {
    if (validateDirPath(tempDir)) {
        _tempDir = tempDir;
    }
}
std::string FileManagement::getTempDirectory() {
    return _tempDir;

}

// Files Management Methods
bool FileManagement::validateDirPath(std::string path)
{
    MapReduceUtils utils;
    if (path.empty()) {
        utils.throwException("FileManagement:validateDirPath", "Path must not be empty.");
    }

    if (boost::starts_with(path, "\"")) {
        path.erase(path.begin());
    }

    if (boost::ends_with(path, "\"")) {
        path.erase(path.end() - 1);
    }

    if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path)) {
        utils.logMessage("Path provided \"" + path + "\" is a valid directory path. Setting value.");
        return true;
    }
    else {
        utils.throwException("FileManagement:validateDirPath", "Path provided \"" + path + "\" is not a valid directory path.");
    }
    return false;
}

void FileManagement::retrieveInputFiles()
{
    MapReduceUtils utils;

    utils.logMessage("Searching for valid text files at provided input path...\n");
    if (boost::filesystem::exists(_inputDir) && boost::filesystem::is_directory(_inputDir))
    {
        for (auto const& entry : boost::filesystem::directory_iterator(_inputDir))
        {
            if (boost::filesystem::is_regular_file(entry) && entry.path().extension() == _ext && !boost::filesystem::is_empty(entry)) {
                _inputPaths.emplace_back(entry.path());
            }

        }
    }
    else
    {
        utils.throwException("FileManagement:get_all","Path provided \"" + _inputDir + "\" is not a valid directory.");
    }
    if (_inputPaths.size() == 0) {
        utils.throwException("FileManagement:get_all", "Path provided \"" + _inputDir + "\" has no valid text files to map and reduce with extension.\"" + _ext + "\"");
    }
}

void FileManagement::executeFileMapping()
{
    MapReduceUtils utils;

    utils.logMessage("Executing File Mapping...\n");
    for (boost::filesystem::path entry : _inputPaths) {
        boost::filesystem::ifstream fileHandler(entry);
        std::string line;
        //create tmp file for fileName, Map/Reduce/Sort will utilize this, with Reduce cleaning up
        std::string fileName = entry.stem().string();
        std::string tmpFileName = _tempDir;
        tmpFileName.append("\\").append(fileName).append("_").append(GetCurrentTimeForFileName()).append(_tmpExt);
        createFile(_tempDir, tmpFileName);
        Map m(fileName, tmpFileName);
        utils.logMessage("\tMapping file \"" + entry.filename().string() + "\"\n");
        while (getline(fileHandler, line)) {
            //pass file name and line to >> Map.map(filename, line)
            m.map(fileName, line);

        }
        //ensure we check the buffer to make sure it does not still have content
        if (m.getExportBufferSize() > 0) {
            m.setPurgeFlag(true);
            m.exportz(fileName, "");
        }
        fileHandler.close();
    }
}

void FileManagement::createFile(std::string directory, std::string filePath)
{
    if(boost::filesystem::is_directory(directory) && !boost::filesystem::exists(filePath)) {
        std::ofstream output(filePath); //create file and not open?
        output.close();
        
    }
}

void FileManagement::writeToFile(std::string filePath, std::string text)
{
   if (boost::filesystem::exists(filePath)) {
        std::fstream fs;
        fs.open(filePath, std::fstream::in | std::fstream::out | std::fstream::app);
        fs << text;
        fs.close();
   }

}

void FileManagement::removeFile(std::string filePath)
{
    if (boost::filesystem::exists(filePath)) {
        boost::filesystem::remove(filePath);
    }
}

std::string FileManagement::GetCurrentTimeForFileName()
{
    const std::string& fmt = "%F_%T";
    std::tm bt{};
    std::time_t timer = time(0);
    localtime_s(&bt, &timer);
    char buf[64];
    std::string timestr = { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
    std::replace(timestr.begin(), timestr.end(), ':', '-');
    return timestr;
}

size_t FileManagement::getInputPathsSize()
{
    return _inputPaths.size();
}
