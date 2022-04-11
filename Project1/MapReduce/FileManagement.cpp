///////////////////////////////////////////////////////////////////
//  FileManagement.cpp -  FileManagement Class                   //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  MapReduce Project 1                            //
//  Course:		  CSE687 SP22 - Object Oriented Design           //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,}@syr.edu                            //
///////////////////////////////////////////////////////////////////

#include "FileManagement.h"
#include "Map.h"
#include <boost/log/trivial.hpp>
#include <boost/algorithm/string/predicate.hpp>
std::string inDirPath, outDirPath, tempDirPath;
std::vector<boost::filesystem::path> paths;


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

void FileManagement::set_input_dir_path(std::string path)
{
    if (validate_dir_path(path)) {
        inDirPath = path;
    }
}

void FileManagement::set_output_dir_path(std::string path)
{
    if (validate_dir_path(path)) {
        outDirPath = path;
    }
}

void FileManagement::set_temp_dir_path(std::string path)
{
    if (validate_dir_path(path)) {
        tempDirPath = path;
    }
}

std::string FileManagement::get_input_dir_path()
{
    return inDirPath;
}

std::string FileManagement::get_output_dir_path()
{
    return outDirPath;
}

std::string FileManagement::get_temp_dir_path()
{
    return tempDirPath;
}

void FileManagement::get_all(boost::filesystem::path const& path, std::string const& ext)
{
    if (path.size() == 0) {
        BOOST_LOG_TRIVIAL(error) << "FileManagement:get_all:Path provided cannot be empty.";
        exit(1);
    }

    if (ext.size() == 0) {
        BOOST_LOG_TRIVIAL(error) << "FileManagement:get_all:Extension provided cannot be empty.";
        exit(1);
    }

    if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path))
    {
        for (auto const& entry : boost::filesystem::directory_iterator(path))
        {
            if (boost::filesystem::is_regular_file(entry) && entry.path().extension() == ext && !boost::filesystem::is_empty(entry)) {
                paths.emplace_back(entry.path());
                BOOST_LOG_TRIVIAL(debug) << entry.path().filename() << std::endl; //debug
            }
                
        }
    }
    else 
    {
        BOOST_LOG_TRIVIAL(error) << "FileManagement:get_all:Path provided \"" << path << "\" is not a valid directory.";
        exit(1);
    }
    if (paths.size() == 0) {
        BOOST_LOG_TRIVIAL(error) << "FileManagement:get_all:Path provided \"" << path << "\" has no valid text files to map and reduce with extension.\"" << ext << "\"";
        exit(1);
    }
}

void FileManagement::execute_file_paths_iteration()
{
    if (paths.size() == 0) {

    }
    Map m;
    for (boost::filesystem::path entry : paths) {
        boost::filesystem::ifstream fileHandler(entry);
        std::string line;
        BOOST_LOG_TRIVIAL(debug) << "Filename: \"" << entry.filename() << "\"" << std::endl; //debug
        while (getline(fileHandler, line)) {
            BOOST_LOG_TRIVIAL(debug) << "Line: >>" << line << std::endl; //debug
            //pass file name and line to >> Map.map(filename, line)
            m.map(entry.filename().string(), line);
        }
    }
}
