//
// Created by Alexander Sherstnev on 2019-01-18.
//

#pragma once

#include "vfs/IVFSDirectory.h"

namespace VFS::Impl
{
    class OSVFSDirectory final : public IVFSDirectory
    {
    public:
        /**
         * Default constructor.
         * @param name {std::string} The object name.
         * @param path {std::string} The object path in file system.
         */
        OSVFSDirectory(std::string name, std::string path)
            : IVFSDirectory(std::move(name), std::move(path)) {}

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
    };
}
