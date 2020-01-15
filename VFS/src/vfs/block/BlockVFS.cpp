//
// Created by Alexander Sherstnev on 2019-01-17.
//

#include "BlockVFS.h"
#include "vfs/VFSException.h"
#include "BlockVFSDirectory.h"
#include "SQL.h"
#include "sqlite.hpp"

using namespace VFS;
using namespace VFS::Impl;

std::shared_ptr<IVFSDirectory> BlockVFS::GetRoot()
{
    io::sqlite::db db(_databasePath);
    io::sqlite::stmt rootDirectoryStmt(db, VFS_BLOCK_SQL_GET_ROOT_DIRECTORY);

    while(rootDirectoryStmt.step())
    {
        int id = rootDirectoryStmt.row().int32(0);
        std::string name(rootDirectoryStmt.row().text(1));
        std::string path(rootDirectoryStmt.row().text(2));

        return std::make_shared<BlockVFSDirectory>(name, path, _databasePath, id);
    }

    throw VFSBlockInvalidStorageException();
}