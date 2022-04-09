/********************************************************
* Filemanagement.cpp -
* CSE687 SP22
* Stephanie Eordanidis & JT Washington
*********************************************************/
#include "FileManagement.h"
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>

string inDirPath, outDirPath, tempDirPath;

bool FileManagement::validate_dir_path(string path)
{
    if (!path.empty() && boost::filesystem::exists(path)) {
        BOOST_LOG_TRIVIAL(info) << "Path provided is valid. Setting value.";
        return true;
    }
    else {
        BOOST_LOG_TRIVIAL(error) << "Invalid path provided.";
        exit(1);
    }
}

void FileManagement::set_input_dir_path(string path)
{
    if (validate_dir_path(path)) {
        inDirPath = path;
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
