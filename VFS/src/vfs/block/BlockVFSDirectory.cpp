//
// Created by Alexander Sherstnev on 2019-01-18.
//

#include "BlockVFSDirectory.h"
#include "BlockVFSFile.h"
#include "vfs/VFSRegistry.h"
#include "SQL.h"
#include "sqlite.hpp"

using namespace VFS;
using namespace VFS::Impl;

void BlockVFSDirectory::Mount(const std::shared_ptr<class IVFS>& vfs)
{
    VFSRegistry::GetInstance().Register(_path, vfs);
}

void BlockVFSDirectory::UnMount()
{
    VFSRegistry::GetInstance().DeRegister(_path);
}

std::list<std::shared_ptr<IVFSObject>> BlockVFSDirectory::GetList() const
{
    std::list<std::shared_ptr<IVFSObject>> result;
    std::shared_ptr<IVFS> vfs = VFSRegistry::GetInstance().GetVFS(_path);
    if (vfs != nullptr)
    {
        result = vfs->GetRoot()->GetList();
    }
    else
    {
        io::sqlite::db db(_databasePath);

        io::sqlite::stmt directoryListStmt(db, VFS_BLOCK_SQL_DIRECTORY_LIST);
        directoryListStmt.bind().int32(1, _id);
        directoryListStmt.bind().int32(2, _id);

        while (directoryListStmt.step())
        {
            int id = directoryListStmt.row().int32(0);
            int type = directoryListStmt.row().int32(1);
            std::string name(directoryListStmt.row().text(2));
            std::string path(directoryListStmt.row().text(3));

            std::shared_ptr<IVFSObject> pushObject = nullptr;
            if (type == VFS_BLOCK_SQL_DIRECTORY_TYPE) { pushObject = std::make_shared<BlockVFSDirectory>(name, path, _databasePath, id); }
            else if (type == VFS_BLOCK_SQL_FILE_TYPE) { pushObject = std::make_shared<BlockVFSFile>(name, path, _databasePath, id); }
            if (pushObject != nullptr) { result.push_back(pushObject); }
        }
    }

    return result;
}

std::shared_ptr<IVFSObject> BlockVFSDirectory::GetObjectByPath(const std::string& path)
{
    std::list<std::shared_ptr<IVFSObject>> objects = GetList();
    for (const auto& object : objects)
    {
        if (object->GetPath() == path)
        {
            return object;
        }
    }

    return nullptr;
}

void BlockVFSDirectory::CreateDirectory(const std::string& name)
{
    std::shared_ptr<IVFS> vfs = VFSRegistry::GetInstance().GetVFS(_path);
    if (vfs != nullptr)
    {
        vfs->GetRoot()->CreateDirectory(name);
    }
    else
    {
        std::string path = _path + name + "/";
        io::sqlite::db db(_databasePath);

        io::sqlite::stmt createDirectoryStmt(db, VFS_BLOCK_SQL_CREATE_DIRECTORY);
        createDirectoryStmt.bind().int32(1, _id);
        createDirectoryStmt.bind().text(2, name);
        createDirectoryStmt.bind().text(3, path);

        createDirectoryStmt.exec();
    }
}

void BlockVFSDirectory::CreateFile(const std::string& name)
{
    std::shared_ptr<IVFS> vfs = VFSRegistry::GetInstance().GetVFS(_path);
    if (vfs != nullptr)
    {
        vfs->GetRoot()->CreateFile(name);
    }
    else
    {
        std::string path = _path + name;
        io::sqlite::db db(_databasePath);

        io::sqlite::stmt createDirectoryStmt(db, VFS_BLOCK_SQL_CREATE_FILE);
        createDirectoryStmt.bind().int32(1, _id);
        createDirectoryStmt.bind().text(2, name);
        createDirectoryStmt.bind().text(3, path);

        createDirectoryStmt.exec();
    }
}