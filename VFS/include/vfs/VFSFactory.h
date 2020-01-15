#include <utility>

#include <utility>

//
// Created by Alexander Sherstnev on 2019-01-17.
//

#pragma once

#include <map>
#include <string>
#include <memory>
#include <exception>
#include "IVFS.h"

namespace VFS
{
    /**
     * Virtual File System Factory.
     */
    class VFSFactory
    {
    public:
        /**
         * Create VFS concrete instance based on name.
         * @param name {std::string} The name of the VFS.
         * @param config {std::map<std::string, std::string>} Other configuration parameters.
         * @return
         */
        static std::shared_ptr<IVFS> Create(const std::string& name, std::map<std::string, std::string>& config);
    };
}
