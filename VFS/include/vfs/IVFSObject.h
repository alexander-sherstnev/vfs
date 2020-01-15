#include <utility>

//
// Created by Alexander Sherstnev on 2019-01-17.
//

#pragma once

#include <string>
#include "IVFSMountPoint.h"

namespace VFS
{
    /**
     * VFS Object Interface.
     */
    class IVFSObject : public IVFSMountPoint
    {
    public:
        /**
         * Default virtual destructor.
         */
        virtual ~IVFSObject() = default;

        /**
         * Get object name.
         * @return {std::string} Object name.
         */
        inline std::string GetName() const { return _name; }

        /**
         * Get object path
         * @return {std::string} Object path.
         */
        inline std::string GetPath() const { return _path; }

    protected:
        /**
         * Default constructor.
         * @param name {std::string} The object name.
         * @param path {std::string} The object path in file system.
         */
        IVFSObject(std::string name, std::string path)
            : _name(std::move(name)), _path(std::move(path)) {}

        // File system object name.
        std::string _name;

        // File system object path.
        std::string _path;
    };
}
