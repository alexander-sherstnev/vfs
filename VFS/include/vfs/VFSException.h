//
// Created by Alexander Sherstnev on 2019-01-18.
//

#pragma once

#include <string>
#include <exception>

namespace VFS
{
    /**
     * Invalid VFS Factory parameter exception.
     */
    class VFSFactoryInvalidParameterException : public std::exception
    {
    public:
        //~ BEGIN std::exception Implementation.
        VFSFactoryInvalidParameterException(std::string name, std::string value)
                : std::exception(), _name(std::move(name)), _value(std::move(value)) {}

        const char* what() const noexcept override
        {
            return std::string("Invalid/Empty VFS Factory parameter: \"" + _name + "\" - \"" + _value + "\"").c_str();
        }
        //~ END std::exception Implementation.

    private:
        std::string _name;
        std::string _value;
    };

    /**
     * Invalid Block storage exception.
     */
    class VFSBlockInvalidStorageException : public std::exception
    {
    public:
        //~ BEGIN std::exception Implementation.
        VFSBlockInvalidStorageException() : std::exception() {}

        const char* what() const noexcept override
        {
            return std::string("Invalid/Empty Block storage").c_str();
        }
        //~ END std::exception Implementation.
    };

    /**
     * Duplicate VFS registration exception.
     */
    class VFSRegistryDuplicateRegistrationException : public std::exception
    {
    public:
        //~ BEGIN std::exception Implementation.
        VFSRegistryDuplicateRegistrationException(std::string path, std::string vfsName)
            : std::exception(), _path(std::move(path)), _vfsName(std::move(vfsName)) {}

        const char* what() const noexcept override
        {
            return std::string("Path \"" + _path + "\" already registered with VFS \"" + _vfsName + "\"").c_str();
        }
        //~ END std::exception Implementation.

    private:
        std::string _path;
        std::string _vfsName;
    };

    /**
     * VFS Registry path not registered exception.
     */
    class VFSRegistryPathNotRegisteredException : public std::exception
    {
    public:
        //~ BEGIN std::exception Implementation.
        VFSRegistryPathNotRegisteredException(std::string path)
                : std::exception(), _path(std::move(path)) {}

        const char* what() const noexcept override
        {
            return std::string("Path \"" + _path + "\" not registered").c_str();
        }
        //~ END std::exception Implementation.

    private:
        std::string _path;
    };
}
