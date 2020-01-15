#include <utility>

//
// Created by Alexander Sherstnev on 2019-01-17.
//

#pragma once

#include <string>
#include "vfs/IVFS.h"

namespace VFS::Impl
{
    /**
     * OS Virtual File System Implementation.
     */
    class OSVFS final : public IVFS
    {
    public:
        /**
         * Default constructor.
         * @param rootDirectory {std::string} The root directory path.
         */
        OSVFS(std::string rootDirectory) : _rootDirectory(std::move(rootDirectory)) {}

        //~ BEGIN IVFS Implementation
        std::string GetName() const override { return "OS"; }
        std::shared_ptr<class IVFSDirectory> GetRoot() override;
        //~ END IVFS Implementation

    private:
        // Root directory path.
        std::string _rootDirectory;
    };
}
