//
// Created by Alexander Sherstnev on 2019-01-17.
//

#include "vfs/VFSRegistry.h"
#include "vfs/VFSException.h"

using namespace VFS;

void VFSRegistry::RegisterRoot(const std::shared_ptr<IVFS>& vfs)
{
    _rootVFS = vfs;
}

void VFSRegistry::Register(const std::string& path, const std::shared_ptr<IVFS>& vfs)
{
    if (_vfs.find(path) != _vfs.end()) { throw VFSRegistryDuplicateRegistrationException(path, vfs->GetName()); }
    _vfs.emplace(path, vfs);
}

void VFSRegistry::DeRegister(const std::string& path)
{
    if (_vfs.find(path) == _vfs.end()) { throw VFSRegistryPathNotRegisteredException(path); }
    _vfs.erase(path);
}

std::shared_ptr<IVFS> VFSRegistry::GetVFS(const std::string& path)
{
    if (_vfs.find(path) == _vfs.end()) { return nullptr; }
    return _vfs[path];
}
