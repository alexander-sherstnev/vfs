//
// Created by Alexander Sherstnev on 2019-01-18.
//

#pragma once

#include "vfs/IVFSFile.h"

namespace VFS::Impl
{
    /**
     * Block Virtual File System Implementation.
     */
    class BlockVFSFile final : public IVFSFile
    {
    public:
        /**
         * Default constructor.
         * @param name {std::string} The object name.
         * @param path {std::string} The object path in file system.
         * @param databasePath {std::string} The path to the VFS database file.
         * @param id {int} The object identifier.
         */
        BlockVFSFile(std::string name, std::string path, std::string databasePath, int id)
            : IVFSFile(std::move(name), std::move(path)), _databasePath(std::move(databasePath)), _id(id) {}

        //~ BEGIN IVFSMountPoint Implementation
        void Mount(const std::shared_ptr<class IVFS>& vfs) override {}
        void UnMount() override {}
        //~ END IVFSMountPoint Implementation

        //~ BEGIN IVFSFile Implementation
        uintmax_t GetSize() const override;
        //~ END IVFSFile Implementation

    private:
        // Path to the database.
        std::string _databasePath;

        // Identifier.
        int _id;
    };
}
