#############################################################################
# Name:        cmake/vfs.cmake
# Purpose:     VFS Manager CMake file
# Author:      Aliaksandr Sharstniou
# Created:     2019-01-12
# Copyright:   (c) 2019 Aliaksandr Sharstniou
# Licence:     MIT
#############################################################################

set(VFS_MANAGER_HDR
        ${SOURCE_DIR}/src/manager/termcolor.hpp)

set(VFS_MANAGER_SRC
        ${SOURCE_DIR}/src/manager/main.cpp)

add_executable(VFSManager ${VFS_MANAGER_SRC}
                          ${VFS_MANAGER_HDR})
target_link_libraries(VFSManager VFS)
target_include_directories(VFSManager PUBLIC ${SOURCE_DIR}/include
                                      PRIVATE ${SOURCE_DIR}/src/manager)