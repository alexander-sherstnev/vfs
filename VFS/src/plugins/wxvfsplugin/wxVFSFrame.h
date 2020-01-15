//
// Created by Alexander Sherstnev on 2019-01-17.
//

#pragma once

#include <memory>
#include <stack>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/textctrl.h>
    #include <wx/treectrl.h>
    #include <wx/imaglist.h>
#endif
#include "vfs/IVFSDirectory.h"
#include "vfs/IVFS.h"

/**
 * Main WX VFS Manager Frame.
 */
class wxVFSFrame : public wxFrame
{
public:
    /**
     * Default constructor.
     * @param title {wxString} The frame title
     * @param pos {wxPoint} The frame position.
     * @param size {wxSize} The frame size.
     * @param vfs {const std::shared_ptr<VFS::IVFS>&} The VFS reference.
     */
    wxVFSFrame(const wxString& title, const wxPoint& pos, const wxSize& size, const std::shared_ptr<VFS::IVFS>& vfs);

private:
    /**
     * Set new current directory.
     * @param newDirectory {const std::shared_ptr<VFS::IVFSDirectory>&} Reference to new directory.
     */
    void SetCurrentDirectory(const std::shared_ptr<VFS::IVFSDirectory>& newDirectory);

    /**
     * Called when tree item activated.
     * @param event {wxTreeEvent&} The tree event.
     */
    void OnTreeItemActivated(wxTreeEvent& event);

    /**
     * Called when tree selected item changed.
     * @param event {wxTreeEvent&} The tree event.
     */
    void OnTreeItemSelChanged(wxTreeEvent& event);

    /**
     * Called when navigation back button clicked.
     * @param event {wxCommandEvent&} The command event.
     */
    void OnNavigationBackClicked(wxCommandEvent& event);

    /**
     * Called when create directory button clicked.
     * @param event {wxCommandEvent&} The command event.
     */
    void OnCreateDirectoryClicked(wxCommandEvent& event);

    /**
     * Called when create file button clicked.
     * @param event {wxCommandEvent&} The command event.
     */
    void OnCreateFileClicked(wxCommandEvent& event);

    /**
     * Called when mount VFS button clicked.
     * @param event {wxCommandEvent&} The command event.
     */
    void OnMountVFSClicked(wxCommandEvent& event);

    // Current VFS directory.
    std::shared_ptr<VFS::IVFSDirectory> _currentDirectory;

    // Current VFS selected directory.
    std::shared_ptr<VFS::IVFSDirectory> _selectedDirectory;

    // Current path text control.
    wxTextCtrl* _currentPath;

    // Navigation stack.
    std::stack<std::shared_ptr<VFS::IVFSDirectory>> _navigationStack;

    // Navigation tree element.
    wxTreeCtrl* _navigationTree;
    static const long _ID_NAVIGATION_TREE;

    // Navigation tree image list.
    wxImageList* _navigationTreeImageList;

    // Navigation tree root item.
    wxTreeItemId _navigationTreeRoot;

    // Navigation back button.
    wxButton* _navigationBackButton;
    static const long _ID_NAVIGATION_BACK_BUTTON;

    // Mount VFS button.
    wxButton* _mountVFSButton;
    static const long _ID_MOUNT_VFS_BUTTON;

    // Create folder button.
    static const long _ID_CREATE_DIRECTORY_BUTTON;

    // Create file button.
    static const long _ID_CREATE_FILE_BUTTON;

    wxDECLARE_EVENT_TABLE();
};
