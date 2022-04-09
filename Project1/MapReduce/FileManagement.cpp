///////////////////////////////////////////////////////////////////
//  FileManagement.cpp -  FileManagement Class                   //
//                                                               //
//  Language:     Visual C++ 2022, ver 17.1.3                    //
//  Application:  Project1, CSE687 SP22 - Object Oriented Design //
//  Authors:      Stephanie Eordanidis                           //
//                JT Washington                                  //
//                Syracuse University                            //
//                {sleordan,}@syr.edu                            //
///////////////////////////////////////////////////////////////////

#include "FileManagement.h"
#include <boost/log/trivial.hpp>
#include <boost/algorithm/string/predicate.hpp>
string inDirPath, outDirPath, tempDirPath;
std::vector<boost::filesystem::path> paths;

bool FileManagement::validate_dir_path(string path)
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
        BOOST_LOG_TRIVIAL(info) << "Path provided \"" << path << "\" is a valid directory path. Setting value.";
        return true;
    }
    else {
        BOOST_LOG_TRIVIAL(error) << "Path provided \"" << path << "\" is not a valid directory path.";
        exit(1);
    }
}

void FileManagement::set_input_dir_path(string path)
{
    if (validate_dir_path(path)) {
        inDirPath = path;
        get_all(inDirPath, ".txt");
    }
}

void FileManagement::set_output_dir_path(string path)
{
    if (validate_dir_path(path)) {
        outDirPath = path;
    }
}

void FileManagement::set_temp_dir_path(string path)
{
    if (validate_dir_path(path)) {
        tempDirPath = path;
    }
}

void FileManagement::get_all(boost::filesystem::path const& path, std::string const& ext)
{
    if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path))
    {
        for (auto const& entry : boost::filesystem::directory_iterator(path))
        {
            if (boost::filesystem::is_regular_file(entry) && entry.path().extension() == ext && !boost::filesystem::is_empty(entry)) {
                paths.emplace_back(entry.path().filename());
                BOOST_LOG_TRIVIAL(debug) << entry.path().filename() << endl; //debug
            }
                
        }
    }
    if (paths.size() == 0) {
        BOOST_LOG_TRIVIAL(error) << "Path provided \"" << path << "\" has no valid text files to map and reduce.";
        exit(1);
    }
}
