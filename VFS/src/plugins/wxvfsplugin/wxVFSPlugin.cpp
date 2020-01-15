//
// Created by Alexander Sherstnev on 2019-01-17.
//

#include "wxVFSPlugin.h"
#include "wxVFSApp.h"
#include <boost/dll/alias.hpp>

wxIMPLEMENT_APP_NO_MAIN(wxVFSApp);
wxIMPLEMENT_WX_THEME_SUPPORT;

void wxVFSPlugin::Init(const std::shared_ptr<VFS::IVFS>& vfs)
{
    int argc = 0;
    char** argv = nullptr;
    wxEntryStart(argc, argv);

    wxVFSApp* app = dynamic_cast<wxVFSApp*>(wxTheApp);
    if (app != nullptr) { app->_vfs = vfs; }

    wxTheApp->OnInit();
}

void wxVFSPlugin::Run()
{
    wxTheApp->OnRun();
}

void wxVFSPlugin::Cleanup()
{
    wxTheApp->OnExit();
    wxEntryCleanup();
}

std::shared_ptr<VFS::IVFSPlugin> wxVFSPlugin::Create()
{
    return std::make_shared<wxVFSPlugin>();
}

BOOST_DLL_ALIAS(
    wxVFSPlugin::Create,
    CreatePlugin
)