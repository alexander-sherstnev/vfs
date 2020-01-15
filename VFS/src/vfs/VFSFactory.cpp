//
// Created by Alexander Sherstnev on 2019-01-17.
//

#include "vfs/VFSFactory.h"
#include "vfs/VFSException.h"
#include "os/OSVFS.h"
#include "block/BlockVFS.h"

using namespace VFS;
using namespace VFS::Impl;

std::shared_ptr<IVFS> VFSFactory::Create(const std::string& name, std::map<std::string, std::string>& config)
{
    // OS VFS
    if (name == "os")
    {
        std::string rootPath = config["-root"];
        if (rootPath.empty()) { throw VFSFactoryInvalidParameterException("-root", rootPath); }

        return std::make_shared<OSVFS>(rootPath);
    }

    // Block VFS
    if (name == "block")
    {
        std::string databasePath = config["-db"];
        if (databasePath.empty()) { throw VFSFactoryInvalidParameterException("-db", databasePath); }

        return std::make_shared<BlockVFS>(databasePath);
    }

    throw VFSFactoryInvalidParameterException("-vfs", name);
}
