#############################################################################
# Name:        cmake/main.cmake
# Purpose:     Main CMake for VFS
# Author:      Aliaksandr Sharstniou
# Created:     2019-01-12
# Copyright:   (c) 2019 Aliaksandr Sharstniou
# Licence:     MIT
#############################################################################

# VFS Library
include(cmake/vfs.cmake)

# Plugins
include(cmake/wxvfsplugin.cmake)

# Manager
include(cmake/vfsmanager.cmake)