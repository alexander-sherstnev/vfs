//
// Created by Alexander Sherstnev on 2019-01-17.
//

#pragma once

#include <string>
#include <map>
#include <memory>
#include "Singleton.hpp"
#include "IVFS.h"

namespace VFS
{
    /**
     * Global Virtual File System Registry.
     */
    class VFSRegistry final : public Singleton<VFSRegistry>
    {
        friend class Singleton<VFSRegistry>;

    public:
        /**
         * Register Root VFS in global registry.
         * @param vfs {const std::shared_ptr<IVFS>&} The Root VFS.
         */
        void RegisterRoot(const std::shared_ptr<IVFS>& vfs);

        /**
         * Register VFS for path in global registry.
         * @param path {const std::string&} The path for which VFS registered.
         * @param vfs {const std::shared_ptr<IVFS>&} The VFS which should be registered.
         */
        void Register(const std::string& path, const std::shared_ptr<IVFS>& vfs);

        /**
         * DeRegister VFS from the path in global registry.
         * @param path {const std::string&} The path for which VFS registered.
         */
        void DeRegister(const std::string& path);

        /**
         * Gets Root VFS.
         * @return {std::shared_ptr<IVFS>} The root VFS reference.
         */
        inline std::shared_ptr<IVFS> GetRoot() const { return _rootVFS; }

        /**
         * Get VFS for path.
         * @param path {const std::string&} The path.
         * @return {std::weak_ptr<IVFS>} The existing VFS or nullptr.
         */
        std::shared_ptr<IVFS> GetVFS(const std::string& path);

        /**
         * Returns true if VFS is exists for specified path.
         * @param path {const std::string&} The path.
         * @return {bool} True if VFS exists.
         */
        inline bool IsVFSExists(const std::string& path) const { return _vfs.find(path) != _vfs.end(); }

    private:
        /**
         * Default constructor.
         */
        VFSRegistry() = default;

        // Root VFS
        std::shared_ptr<IVFS> _rootVFS;

        // Mounted VFS
        std::map<std::string, std::shared_ptr<IVFS>> _vfs;
    };
}
