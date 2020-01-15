//
// Created by Alexander Sherstnev on 2019-01-17.
//

#pragma once

#include "IVFSObject.h"

namespace VFS
{
    /**
     * Virtual File System File Interface.
     */
    class IVFSFile : public IVFSObject
    {
    public:
        /**
         * Get size in bytes of the file.
         * @return {uintmax_t} The file size in bytes.
         */
        virtual uintmax_t GetSize() const = 0;

    protected:
        /**
         * Default constructor.
         * @param name {std::string} The object name.
         * @param path {std::string} The object path in file system.
         */
        IVFSFile(std::string name, std::string path)
            : IVFSObject(std::move(name), std::move(path)) {}
    };
}
