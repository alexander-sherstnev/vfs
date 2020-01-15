//
// Created by Alexander Sherstnev on 2019-01-17.
//

#pragma once

#include <list>
#include <memory>
#include "IVFSObject.h"

namespace VFS
{
    /**
     * Virtual File System Directory Interface.
     */
    class IVFSDirectory : public IVFSObject
    {
    public:
        /**
         * Get a list of VFS objects in a directory.
         * @return {std::list<std::shared_ptr<IVFSObject>>} The list of objects.
         */
        virtual std::list<std::shared_ptr<IVFSObject>> GetList() const = 0;

        /**
         * Get object by provided path or if not found return nullptr.
         * @param path {const std::string&} The object path.
         * @return {std::shared_ptr<IVFSObject>} The found object or nullptr.
         */
        virtual std::shared_ptr<IVFSObject> GetObjectByPath(const std::string& path) = 0;

        /**
         * Create new directory in current.
         * @param name {const std::string&} The directory name.
         */
        virtual void CreateDirectory(const std::string& name) = 0;

        /**
         * Create new file in current directory.
         * @param name {const std::string&} The file name.
         */
        virtual void CreateFile(const std::string& name) = 0;

    protected:
        /**
         * Default constructor.
         * @param name {std::string} The object name.
         * @param path {std::string} The object path in file system.
         */
        IVFSDirectory(std::string name, std::string path)
            : IVFSObject(std::move(name), std::move(path)) {}
    };
}
