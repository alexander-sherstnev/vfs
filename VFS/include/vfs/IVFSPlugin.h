//
// Created by Alexander Sherstnev on 2019-01-17.
//

#pragma once

#include <memory>
#include "IVFS.h"

namespace VFS
{
    /**
     * Virtual File System Plugin Interface.
     */
    class IVFSPlugin
    {
    public:
        /**
         * Default virtual destructor.
         */
        virtual ~IVFSPlugin() = default;

        /**
         * Initialize plugin.
         * @param vfs {const std::shared_ptr<IVFS>&} The VFS.
         */
        virtual void Init(const std::shared_ptr<IVFS>& vfs) = 0;

        /**
         * Run plugin logic.
         */
        virtual void Run() = 0;

        /**
         * Cleanup plugin.
         */
        virtual void Cleanup() = 0;
    };
}
