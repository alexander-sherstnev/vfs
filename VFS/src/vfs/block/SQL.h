//
// Created by Alexander Sherstnev on 2019-01-18.
//

#pragma once

#define VFS_BLOCK_SQL_DIRECTORY_TYPE 0
#define VFS_BLOCK_SQL_FILE_TYPE 1
#define VFS_BLOCK_SQL_GET_ROOT_DIRECTORY "SELECT id, name, path FROM vfs_object WHERE id = parent_id AND type = 0 LIMIT 1;"
#define VFS_BLOCK_SQL_DIRECTORY_LIST "SELECT id, type, name, path FROM vfs_object WHERE id <> ? AND parent_id = ?;"
#define VFS_BLOCK_SQL_CREATE_DIRECTORY "INSERT INTO vfs_object (parent_id, type, name, path, size) VALUES (?, 0, ?, ?, 0);"
#define VFS_BLOCK_SQL_CREATE_FILE "INSERT INTO vfs_object (parent_id, type, name, path, size) VALUES (?, 1, ?, ?, 0);"
