//
// Created by Alexander Sherstnev on 2019-01-17.
//

#pragma once

#include "vfs/IVFS.h"

namespace VFS::Impl
{
    /**
     * Block (one file) Virtual File System Implementation.
     * NOTE: This implementation is using SQLite3 database as block storage with next schema
     *
     * create table vfs_object
     * (
     *     id INTEGER
     *         constraint vfs_object_pk
     *             primary key autoincrement,
     *     parent_id INTEGER not null
     *         references vfs_object
     *             on update cascade on delete cascade,
     *     type INTEGER not null,
     *     name TEXT not null,
     *     path TEXT not null,
     *     size INTEGER not null,
     *     data BLOB
     * );
     *
     * create unique index vfs_object_name_uindex
     *     on vfs_object (name);
     *
     * create unique index vfs_object_path_uindex
     *     on vfs_object (path);
     *
     */
    class BlockVFS final : public IVFS
    {
    public:
        /**
         * Default constructor.
         * @param databasePath {std::string} The path to database file.
         */
        BlockVFS(std::string databasePath) : _databasePath(std::move(databasePath)) {}

        //~ BEGIN IVFS Implementation
        std::string GetName() const override { return "Block"; }
        std::shared_ptr<class IVFSDirectory> GetRoot() override;
        //~ END IVFS Implementation

    private:
        // Database file path.
        std::string _databasePath;
    };
}
