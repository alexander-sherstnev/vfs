//
// Created by Alexander Sherstnev on 2019-01-17.
//

#pragma once

#include <memory>
#include "vfs/IVFSPlugin.h"
#include "vfs/IVFS.h"

/**
 * wxWidget VFS Plugin Implementation.
 */
class wxVFSPlugin : public VFS::IVFSPlugin
{
public:
    //~  BEGIN IVFSPlugin Implementation
    void Init(const std::shared_ptr<VFS::IVFS>& vfs) override;
    void Run() override;
    void Cleanup() override;
    //~  END IVFSPlugin Implementation

    /**
     * Factory method which create plugin instance.
     * @return {std::shared_ptr<VFS::IVFSPlugin>} The plugin instance reference.
     */
    static std::shared_ptr<VFS::IVFSPlugin> Create();
};
