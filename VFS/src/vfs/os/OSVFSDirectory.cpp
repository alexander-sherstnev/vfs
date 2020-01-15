//
// Created by Alexander Sherstnev on 2019-01-18.
//

#include "OSVFSDirectory.h"
#include "OSVFSFile.h"
#include "vfs/VFSRegistry.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/range/iterator_range.hpp>

using namespace VFS;
using namespace VFS::Impl;

void OSVFSDirectory::Mount(const std::shared_ptr<class IVFS>& vfs)
{
    VFSRegistry::GetInstance().Register(_path, vfs);
}

void OSVFSDirectory::UnMount()
{
    VFSRegistry::GetInstance().DeRegister(_path);
}

std::list<std::shared_ptr<IVFSObject>> OSVFSDirectory::GetList() const
{
    std::list<std::shared_ptr<IVFSObject>> result;
    std::shared_ptr<IVFS> vfs = VFSRegistry::GetInstance().GetVFS(_path);
    if (vfs != nullptr)
    {
        result = vfs->GetRoot()->GetList();
    }
    else
    {
        for (auto& object : boost::make_iterator_range(boost::filesystem::directory_iterator(_path), {}))
        {
            std::string objectName = object.path().filename().string();
            std::string objectPath = object.path().string();

            std::shared_ptr<IVFSObject> pushObject = nullptr;
            if (boost::filesystem::is_directory(object.path()))
            {
                pushObject = std::make_shared<OSVFSDirectory>(objectName, objectPath);
            }
            else if (boost::filesystem::is_regular_file(object.path()))
            {
                pushObject = std::make_shared<OSVFSFile>(objectName, objectPath);
            }
            if (pushObject != nullptr) { result.push_back(pushObject); }
        }
    }

    return result;
}

std::shared_ptr<IVFSObject> OSVFSDirectory::GetObjectByPath(const std::string& path)
{
    std::list<std::shared_ptr<IVFSObject>> objects = GetList();
    for (const auto& object : objects)
    {
        if (object->GetPath() == path)
        {
            return object;
        }
    }

    return nullptr;
}

void OSVFSDirectory::CreateDirectory(const std::string& name)
{
    std::shared_ptr<IVFS> vfs = VFSRegistry::GetInstance().GetVFS(_path);
    if (vfs != nullptr)
    {
        vfs->GetRoot()->CreateDirectory(name);
    }
    else
    {
        boost::filesystem::path directoryPath(_path);
        directoryPath.append(name);
        if (!boost::filesystem::exists(directoryPath))
        {
            boost::filesystem::create_directory(directoryPath);
        }
    }
}

void OSVFSDirectory::CreateFile(const std::string& name)
{
    std::shared_ptr<IVFS> vfs = VFSRegistry::GetInstance().GetVFS(_path);
    if (vfs != nullptr)
    {
        vfs->GetRoot()->CreateFile(name);
    }
    else
    {
        boost::filesystem::path filePath(_path);
        filePath.append(name);
        if (!boost::filesystem::exists(filePath))
        {
            std::ofstream file(filePath.string());
            file.close();
        }
    }
}
