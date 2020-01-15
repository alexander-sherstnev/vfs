#include <utility>

//
// Created by Alexander Sherstnev on 2019-01-18.
//

#pragma once

#include "vfs/IVFSDirectory.h"

namespace VFS::Impl
{
    /**
     * Block Virtual File System Implementation.
     */
    class BlockVFSDirectory final : public IVFSDirectory
    {
    public:
        /**
         * Default constructor.
         * @param name {std::string} The object name.
         * @param path {std::string} The object path in file system.
         * @param databasePath {std::string} The path to the VFS database file.
         * @param id {int} The object identifier.
         */
        BlockVFSDirectory(std::string name, std::string path, std::string databasePath, int id)
            : IVFSDirectory(std::move(name), std::move(path)), _databasePath(std::move(databasePath)), _id(id) {}

        //~ BEGIN IVFSMountPoint Implementation
        void Mount(const std::shared_ptr<class IVFS>& vfs) override;
        void UnMount() override;
        //~ END IVFSMountPoint Implementation

        //~ BEGIN IVFSDirectory Implementation
        std::list<std::shared_ptr<IVFSObject>> GetList() const override;
        std::shared_ptr<IVFSObject> GetObjectByPath(const std::string& path) override;
        void CreateDirectory(const std::string& name) override;
        void CreateFile(const std::string& name) override;
        //~ END IVFSDirectory Implementation

    private:
        // Path to the database.
        std::string _databasePath;

        // Identifier.
        int _id;
    };
}
