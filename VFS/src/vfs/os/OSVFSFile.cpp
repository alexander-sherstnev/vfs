//
// Created by Alexander Sherstnev on 2019-01-18.
//

#include "OSVFSFile.h"
#include <boost/filesystem.hpp>

using namespace VFS;
using namespace VFS::Impl;

uintmax_t OSVFSFile::GetSize() const
{
    return boost::filesystem::file_size(_path);
}