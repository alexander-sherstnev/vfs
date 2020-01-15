//
// Created by Alexander Sherstnev on 2019-01-17.
//

#include "wxVFSApp.h"
#include "wxVFSFrame.h"

bool wxVFSApp::OnInit()
{
    wxVFSFrame* frame = new wxVFSFrame("wxVFSManager", wxPoint(100, 100), wxSize(800, 600), _vfs);
    frame->Show(true);

    return true;
}