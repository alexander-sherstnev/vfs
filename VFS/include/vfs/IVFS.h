//
// Created by Alexander Sherstnev on 2019-01-17.
//

#pragma once

#include <string>
#include <memory>

namespace VFS
{
    /**
     * Virtual File System Interface.
     */
    class IVFS
    {
    public:
        /**
         * Default virtual destructor.
         */
        virtual ~IVFS() = default;

        /**
         * Get name of the Virtual File System.
         * @return {std::string} The name of the VFS.
         */
        virtual std::string GetName() const = 0;

        /**
         * Get Root Directory of the VFS.
         * @return {std::shared_ptr<IVFSDirectory>} The Root Directory Object.
         */
        virtual std::shared_ptr<class IVFSDirectory> GetRoot() = 0;
    };
}
