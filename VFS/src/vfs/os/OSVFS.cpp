//
// Created by Alexander Sherstnev on 2019-01-17.
//

#include "OSVFS.h"
#include "OSVFSDirectory.h"

using namespace VFS;
using namespace VFS::Impl;

std::shared_ptr<IVFSDirectory> OSVFS::GetRoot()
{
    return std::make_shared<OSVFSDirectory>("Root", _rootDirectory);
}