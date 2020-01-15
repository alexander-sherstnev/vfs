//
// Created by Alexander Sherstnev on 2019-01-18.
//

#pragma once

#include "vfs/IVFSFile.h"

namespace VFS::Impl
{
    class OSVFSFile final : public IVFSFile
    {
    public:
        /**
         * Default constructor.
         * @param name {std::string} The object name.
         * @param path {std::string} The object path in file system.
         */
        OSVFSFile(std::string name, std::string path)
            : IVFSFile(std::move(name), std::move(path)) {}

        //~ BEGIN IVFSMountPoint Implementation
        void Mount(const std::shared_ptr<class IVFS>& vfs) override {}
        void UnMount() override {}
        //~ END IVFSMountPoint Implementation

        //~ BEGIN IVFSFile Implementation
        uintmax_t GetSize() const override;
        //~ END IVFSFile Implementation
    };
}

