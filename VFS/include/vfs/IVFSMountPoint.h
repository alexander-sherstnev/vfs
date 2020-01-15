//
// Created by Alexander Sherstnev on 2019-01-17.
//

#pragma once

#include <memory>

namespace VFS
{
    /**
     * Mount Point Interface.
     */
    class IVFSMountPoint
    {
    public:
        /**
         * Default virtual destructor.
         */
        virtual ~IVFSMountPoint() = default;

        /**
         * Mount VFS to the current point.
         * @param vfs {std::shared_ptr<class IVFS>} The mounting VFS.
         */
        virtual void Mount(const std::shared_ptr<class IVFS>& vfs) = 0;

        /**
         * UnMount VFS from the current point.
         */
        virtual void UnMount() = 0;
    };
}
