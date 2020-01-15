//
// Created by Alexander Sherstnev on 2019-01-17.
//

#include "wxVFSFrame.h"
#include <iostream>
#include <sstream>
#include <map>
#include <wx/artprov.h>
#include <wx/textdlg.h>
#include "vfs/VFSRegistry.h"
#include "vfs/VFSFactory.h"

#define FOLDER_IMAGE_INDEX 0
#define FILE_IMAGE_INDEX 1

/**
 * Custom navigation tree item data.
 */
class NavigationTreeItemData : public wxTreeItemData
{
public:
    /**
     * Default constructor.
     * @param path {std::string} The item path.
     */
    NavigationTreeItemData(std::string path) : _path(std::move(path)) {}

    /**
     * Get path value from item data.
     * @return {std::string} The item path data.
     */
    inline std::string GetPath() const { return _path; }

private:
    // Item path.
    std::string _path;
};

/**
 * Helper method which parse parameters from input string.
 * @param input {const std::string&} The input string.
 * @return {std::map<std::string, std::string>} The parsed parameters.
 */
std::map<std::string, std::string> ParseParameters(const std::string& input)
{
    std::map<std::string, std::string> result;
    std::istringstream inputStream(input);
    std::string parameterName;
    std::string argument;
    bool parameterFound = false;
    while(std::getline(inputStream, argument, ' '))
    {
        if (!argument.empty())
        {
            if (parameterFound)
            {
                result.emplace(parameterName, argument);
                parameterFound = false;
                parameterName = "";
            }
            else if (argument[0] == '-')
            {
                parameterFound = true;
                parameterName = argument;
                continue;
            }
        }
    }

    return result;
}

// IDs
const long wxVFSFrame::_ID_NAVIGATION_TREE = wxNewId();
const long wxVFSFrame::_ID_NAVIGATION_BACK_BUTTON = wxNewId();
const long wxVFSFrame::_ID_MOUNT_VFS_BUTTON = wxNewId();
const long wxVFSFrame::_ID_CREATE_DIRECTORY_BUTTON = wxNewId();
const long wxVFSFrame::_ID_CREATE_FILE_BUTTON = wxNewId();

wxBEGIN_EVENT_TABLE(wxVFSFrame, wxFrame)
    EVT_TREE_ITEM_ACTIVATED(wxVFSFrame::_ID_NAVIGATION_TREE, wxVFSFrame::OnTreeItemActivated)
    EVT_TREE_SEL_CHANGED(wxVFSFrame::_ID_NAVIGATION_TREE, wxVFSFrame::OnTreeItemSelChanged)
    EVT_BUTTON(wxVFSFrame::_ID_NAVIGATION_BACK_BUTTON, wxVFSFrame::OnNavigationBackClicked)
    EVT_BUTTON(wxVFSFrame::_ID_CREATE_DIRECTORY_BUTTON, wxVFSFrame::OnCreateDirectoryClicked)
    EVT_BUTTON(wxVFSFrame::_ID_CREATE_FILE_BUTTON, wxVFSFrame::OnCreateFileClicked)
    EVT_BUTTON(wxVFSFrame::_ID_MOUNT_VFS_BUTTON, wxVFSFrame::OnMountVFSClicked)
wxEND_EVENT_TABLE()

wxVFSFrame::wxVFSFrame(const wxString& title, const wxPoint& pos, const wxSize& size, const std::shared_ptr<VFS::IVFS>& vfs)
    : wxFrame(nullptr, wxID_ANY, title, pos, size, wxSYSTEM_MENU | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)
{
    CreateStatusBar();

    wxBoxSizer* mainContainer = new wxBoxSizer(wxVERTICAL);

    // Path Status Bar
    wxBoxSizer* pathContainer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* pathLabel = new wxStaticText(this, wxID_ANY, _("Path:"));
    _currentPath = new wxTextCtrl(this, wxID_ANY,_(""), wxDefaultPosition, wxSize(300, 20), wxTE_READONLY);
    pathContainer->Add(pathLabel, wxSizerFlags().Align(wxALIGN_LEFT | wxALIGN_CENTRE_VERTICAL).Border(wxALL, 0));
    pathContainer->Add(_currentPath, wxSizerFlags().Align(wxALIGN_LEFT).Border(wxLEFT, 5));
    mainContainer->Add(pathContainer, wxSizerFlags().Align(wxALIGN_LEFT).Border(wxALL, 10));

    // Navigation
    wxBoxSizer* navigationContainer = new wxBoxSizer(wxVERTICAL);
    _navigationTreeImageList = new wxImageList(16, 16);
    _navigationTreeImageList->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16, 16)));
    _navigationTreeImageList->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16)));

    _navigationTree = new wxTreeCtrl(this, _ID_NAVIGATION_TREE, wxDefaultPosition, wxSize(340, 400));
    _navigationTree->AssignImageList(_navigationTreeImageList);

    _navigationTreeRoot = _navigationTree->AddRoot("Empty", FOLDER_IMAGE_INDEX);

    navigationContainer->Add(_navigationTree, wxSizerFlags().Align(wxALIGN_LEFT).Border(wxALL, 0));
    mainContainer->Add(navigationContainer, wxSizerFlags().Align(wxALIGN_LEFT).Border(wxALL & ~wxTOP, 10));

    // Controls
    wxBoxSizer* controlsContainer = new wxBoxSizer(wxHORIZONTAL);

    _navigationBackButton = new wxButton(this, _ID_NAVIGATION_BACK_BUTTON, _("Back"), wxDefaultPosition, wxSize(50, 20));
    _navigationBackButton->SetLabelMarkup("<span foreground='black'>Back</span>");
    _navigationBackButton->Enable(false);

    wxButton* createDirectoryButton = new wxButton(this, _ID_CREATE_DIRECTORY_BUTTON, _("Create Folder"), wxDefaultPosition, wxSize(100, 20));
    createDirectoryButton->SetLabelMarkup("<span foreground='black'>" + _("Create Folder") + "</span>");

    wxButton* createFileButton = new wxButton(this, _ID_CREATE_FILE_BUTTON, _("Create File"), wxDefaultPosition, wxSize(80, 20));
    createFileButton->SetLabelMarkup("<span foreground='black'>" + _("Create File") + "</span>");

    _mountVFSButton = new wxButton(this, _ID_MOUNT_VFS_BUTTON, _("Mount"), wxDefaultPosition, wxSize(70, 20));
    _mountVFSButton->SetLabelMarkup("<span foreground='black'>" + _("Mount") + "</span>");
    _mountVFSButton->Enable(false);

    controlsContainer->Add(_navigationBackButton, wxSizerFlags().Align(wxALIGN_CENTER).Border(wxALL, 5));
    controlsContainer->Add(createDirectoryButton, wxSizerFlags().Align(wxALIGN_CENTER).Border(wxALL, 5));
    controlsContainer->Add(createFileButton, wxSizerFlags().Align(wxALIGN_CENTER).Border(wxALL, 5));
    controlsContainer->Add(_mountVFSButton, wxSizerFlags().Align(wxALIGN_CENTER).Border(wxALL, 5));
    mainContainer->Add(controlsContainer, wxSizerFlags().Align(wxALIGN_LEFT).Border(wxALL & ~wxTOP, 10));

    SetCurrentDirectory(vfs->GetRoot());

    SetSizerAndFit(mainContainer);
}

void wxVFSFrame::SetCurrentDirectory(const std::shared_ptr<VFS::IVFSDirectory>& newDirectory)
{
    if (newDirectory == nullptr) { return; }

    _currentDirectory = newDirectory;
    _currentPath->ChangeValue(_currentDirectory->GetPath());

    _navigationTree->DeleteChildren(_navigationTreeRoot);
    _navigationTree->SetItemText(_navigationTreeRoot, _currentDirectory->GetName());
    for (const auto& object : _currentDirectory->GetList())
    {
        int imageIndex = std::dynamic_pointer_cast<VFS::IVFSDirectory>(object) != nullptr ? FOLDER_IMAGE_INDEX : FILE_IMAGE_INDEX;
        std::string itemName = object->GetName();
        std::shared_ptr<VFS::IVFS> mountedVFS = VFS::VFSRegistry::GetInstance().GetVFS(object->GetPath());
        if (mountedVFS != nullptr) { itemName += " (Mounted: \""+ mountedVFS->GetName() + "\")"; }
        _navigationTree->AppendItem(_navigationTreeRoot, itemName, imageIndex, -1, new NavigationTreeItemData(object->GetPath()));
    }
    _navigationTree->ExpandAll();
}

void wxVFSFrame::OnTreeItemActivated(wxTreeEvent& event)
{
    NavigationTreeItemData* itemData = dynamic_cast<NavigationTreeItemData*>(event.GetClientObject());
    if (itemData != nullptr && _currentDirectory != nullptr)
    {
        std::shared_ptr<VFS::IVFSObject> object = _currentDirectory->GetObjectByPath(itemData->GetPath());
        if (object != nullptr)
        {
            std::shared_ptr<VFS::IVFSDirectory> newDirectory = std::dynamic_pointer_cast<VFS::IVFSDirectory>(object);
            if (newDirectory != nullptr)
            {
                _navigationStack.push(_currentDirectory);
                _navigationBackButton->Enable(true);
                SetCurrentDirectory(newDirectory);
            }
        }
    }
}

void wxVFSFrame::OnTreeItemSelChanged(wxTreeEvent& event)
{
    _selectedDirectory = nullptr;
    NavigationTreeItemData* itemData = dynamic_cast<NavigationTreeItemData*>(event.GetClientObject());
    if (itemData != nullptr && _currentDirectory != nullptr)
    {
        std::shared_ptr<VFS::IVFSObject> object = _currentDirectory->GetObjectByPath(itemData->GetPath());
        if (object != nullptr)
        {
            std::shared_ptr<VFS::IVFSDirectory> directory = std::dynamic_pointer_cast<VFS::IVFSDirectory>(object);
            if (directory != nullptr)
            {
                _selectedDirectory = directory;
                _mountVFSButton->SetLabelMarkup("<span foreground='black'>" + (VFS::VFSRegistry::GetInstance().IsVFSExists(_selectedDirectory->GetPath()) ? _("UnMount") : _("Mount")) + + "</span>");
                _mountVFSButton->Enable(true);
            }
        }
    }
    else
    {
        _mountVFSButton->SetLabelMarkup("<span foreground='black'>" + _("Mount") + "</span>");
        _mountVFSButton->Enable(false);
    }
}

void wxVFSFrame::OnNavigationBackClicked(wxCommandEvent& event)
{
    if (!_navigationStack.empty())
    {
        std::shared_ptr<VFS::IVFSDirectory> prevDirectory = _navigationStack.top();
        _navigationStack.pop();
        if (prevDirectory != nullptr) { SetCurrentDirectory(prevDirectory); }
    }

    if (_navigationStack.empty()) { _navigationBackButton->Enable(false); }
}

void wxVFSFrame::OnCreateDirectoryClicked(wxCommandEvent& event)
{
    wxTextEntryDialog directoryNameDialog(this, _("Enter directory name:"), _("Please enter directory name"));
    if (directoryNameDialog.ShowModal() == wxID_OK)
    {
        std::string directoryName(directoryNameDialog.GetValue().mbc_str());
        if (!directoryName.empty() && _currentDirectory != nullptr)
        {
            _currentDirectory->CreateDirectory(directoryName);
            SetCurrentDirectory(_currentDirectory);
        }
    }
}

void wxVFSFrame::OnCreateFileClicked(wxCommandEvent& event)
{
    wxTextEntryDialog fileNameDialog(this, _("Enter file name:"), _("Please enter file name"));
    if (fileNameDialog.ShowModal() == wxID_OK)
    {
        std::string fileName(fileNameDialog.GetValue().mbc_str());
        if (!fileName.empty() && _currentDirectory != nullptr)
        {
            _currentDirectory->CreateFile(fileName);
            SetCurrentDirectory(_currentDirectory);
        }
    }
}

void wxVFSFrame::OnMountVFSClicked(wxCommandEvent& event)
{
    if (_selectedDirectory != nullptr)
    {
        if (VFS::VFSRegistry::GetInstance().IsVFSExists(_selectedDirectory->GetPath()))
        {
            _selectedDirectory->UnMount();
        }
        else
        {
            wxTextEntryDialog mountVFSDialog(this, _("Enter VFS parameters:"), _("Please enter VFS parameter"));
            if (mountVFSDialog.ShowModal() == wxID_OK)
            {
                std::string mountVFSInput(mountVFSDialog.GetValue().mbc_str());
                if (!mountVFSInput.empty())
                {
                    try
                    {
                        std::map<std::string, std::string> parameters = ParseParameters(mountVFSInput);
                        std::shared_ptr<VFS::IVFS> vfs = VFS::VFSFactory::Create(parameters["-vfs"], parameters);

                        _selectedDirectory->Mount(vfs);
                    }
                    catch (std::exception& e)
                    {
                        std::string what(e.what());
                        std::cout << what << std::endl;
                    }
                }
            }
        }

        SetCurrentDirectory(_currentDirectory);
    }
}