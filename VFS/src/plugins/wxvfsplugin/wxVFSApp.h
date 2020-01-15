//
// Created by Alexander Sherstnev on 2019-01-17.
//

#pragma once

#include <memory>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "vfs/IVFS.h"

/**
 * wxWidget VFS Plugin Application.
 */
class wxVFSApp : public wxApp
{
    friend class wxVFSPlugin;

public:
    //~ BEGIN wxApp Implementation
    virtual bool OnInit() override;
    //~ END wxApp Implementation

private:
    // Reference to VFS
    std::shared_ptr<VFS::IVFS> _vfs;
};
