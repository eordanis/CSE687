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
#include <boost/log/trivial.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <vector>
#include <boost/filesystem/fstream.hpp>
#include <iostream>
#include <iterator>
#include <map>
#include <fstream>


// Get + Set Methods for File Management Class
void FileManagement::setInputDirectory(std::string inputDir) {
    _inputDir = inputDir;
}
std::string FileManagement::getInputDirectory() {
    return _inputDir;

}

void FileManagement::setOutputDirectory(std::string outputDir) {
    _outputDir = outputDir;
}
std::string FileManagement::getOutputDirectory() {
    return _outputDir;

}

void FileManagement::setTempDirectory(std::string tempDir) {
    _tempDir = tempDir;
}
std::string FileManagement::getTempDirectory() {
    return _tempDir;

}

// Files Management Methods
bool FileManagement::validate_dir_path(std::string path)
{
    if (path.empty()) {
        BOOST_LOG_TRIVIAL(error) << "Path must not be empty";
        return true;
    }

    if (boost::starts_with(path, "\"")) {
        path.erase(path.begin());
    }

    if (boost::ends_with(path, "\"")) {
        path.erase(path.end() - 1);
    }

    if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path)) {
        BOOST_LOG_TRIVIAL(info) << "FileManagement:validate_dir_path:Path provided \"" << path << "\" is a valid directory path. Setting value.";
        return true;
    }
    else {
        BOOST_LOG_TRIVIAL(error) << "FileManagement:validate_dir_path:Path provided \"" << path << "\" is not a valid directory path.";
        exit(1);
    }
}

void FileManagement::retrieveInputFiles()
{

    if (boost::filesystem::exists(_inputDir) && boost::filesystem::is_directory(_inputDir))
    {
        for (auto const& entry : boost::filesystem::directory_iterator(_inputDir))
        {
            if (boost::filesystem::is_regular_file(entry) && entry.path().extension() == _ext && !boost::filesystem::is_empty(entry)) {
                _inputPaths.emplace_back(entry.path());
                BOOST_LOG_TRIVIAL(debug) << entry.path().filename() << std::endl; //debug
            }

        }
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "FileManagement:get_all:Path provided \"" << _inputDir << "\" is not a valid directory.";
        exit(1);
    }
    if (_inputPaths.size() == 0) {
        BOOST_LOG_TRIVIAL(error) << "FileManagement:get_all:Path provided \"" << _inputDir << "\" has no valid text files to map and reduce with extension.\"" << _ext << "\"";
        exit(1);
    }
}

void FileManagement::executeFileMapping()
{
    Map m;
    for (boost::filesystem::path entry : _inputPaths) {
        
        boost::filesystem::ifstream fileHandler(entry);
        std::string line;
        BOOST_LOG_TRIVIAL(debug) << "Filename: \"" << entry.filename().string() << "\"" << std::endl; //debug
        //create tmp file for fileName, Map/Reduce/Sort will utilize this, with Reduce cleaning up
        std::string tmpFileName = _tempDir;
        tmpFileName.append("\\").append(entry.stem().string()).append(".dat");
        createFile(tmpFileName);
        while (getline(fileHandler, line)) {
            BOOST_LOG_TRIVIAL(debug) << "Line: >>" << line << std::endl; //debug
            //pass file name and line to >> Map.map(filename, line)
            m.map(entry.stem().string(), line);
        }
    }
}

void FileManagement::createFile(std::string filePath)
{
    if(!boost::filesystem::exists(filePath)) {
        BOOST_LOG_TRIVIAL(debug) << "Creating File: >>" << filePath << std::endl; //debug
        std::fstream tf(filePath); //create the file and close stream
        tf.close();
    }
}

void FileManagement::writeToFile(std::string filePath, std::string text)
{
   if (boost::filesystem::exists(filePath)) {
        BOOST_LOG_TRIVIAL(debug) << "Writting to File: >>" << filePath << std::endl; //debug
        std::fstream fs;
        fs.open(filePath, std::fstream::in | std::fstream::out | std::fstream::app);
        fs << text;
        fs.close();
   }

}

void FileManagement::removeFile(std::string filePath)
{
    if (boost::filesystem::exists(filePath)) {
        BOOST_LOG_TRIVIAL(debug) << "Removing File: >>" << filePath << std::endl; //debug
        boost::filesystem::remove(filePath);
    }

}
