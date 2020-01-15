#############################################################################
# Name:        cmake/vfs.cmake
# Purpose:     VFS CMake file
# Author:      Aliaksandr Sharstniou
# Created:     2019-01-12
# Copyright:   (c) 2019 Aliaksandr Sharstniou
# Licence:     MIT
#############################################################################

# Boost Library
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})

# SQLite3 Library
find_package(SQLite3)
include_directories(${SQLITE3_INCLUDE_DIRS})

set(VFS_HDR
        ${SOURCE_DIR}/include/vfs/Singleton.hpp

        ${SOURCE_DIR}/include/vfs/VFSException.h

        ${SOURCE_DIR}/include/vfs/IVFS.h
        ${SOURCE_DIR}/include/vfs/IVFSMountPoint.h
        ${SOURCE_DIR}/include/vfs/IVFSObject.h
        ${SOURCE_DIR}/include/vfs/IVFSFile.h
        ${SOURCE_DIR}/include/vfs/IVFSDirectory.h
        ${SOURCE_DIR}/include/vfs/IVFSPlugin.h

        ${SOURCE_DIR}/include/vfs/VFSFactory.h
        ${SOURCE_DIR}/include/vfs/VFSRegistry.h)

set(VFS_SRC
        ${SOURCE_DIR}/src/vfs/os/OSVFS.h
        ${SOURCE_DIR}/src/vfs/os/OSVFS.cpp
        ${SOURCE_DIR}/src/vfs/os/OSVFSFile.h
        ${SOURCE_DIR}/src/vfs/os/OSVFSFile.cpp
        ${SOURCE_DIR}/src/vfs/os/OSVFSDirectory.h
        ${SOURCE_DIR}/src/vfs/os/OSVFSDirectory.cpp

        ${SOURCE_DIR}/src/vfs/block/sqlite.hpp
        ${SOURCE_DIR}/src/vfs/block/sqlite.cpp
        ${SOURCE_DIR}/src/vfs/block/SQL.h
        ${SOURCE_DIR}/src/vfs/block/BlockVFS.h
        ${SOURCE_DIR}/src/vfs/block/BlockVFS.cpp
        ${SOURCE_DIR}/src/vfs/block/BlockVFSFile.h
        ${SOURCE_DIR}/src/vfs/block/BlockVFSFile.cpp
        ${SOURCE_DIR}/src/vfs/block/BlockVFSDirectory.h
        ${SOURCE_DIR}/src/vfs/block/BlockVFSDirectory.cpp

        ${SOURCE_DIR}/src/vfs/VFSFactory.cpp
        ${SOURCE_DIR}/src/vfs/VFSRegistry.cpp)

add_library(VFS STATIC ${VFS_SRC}
                       ${VFS_HDR})
target_link_libraries(VFS ${Boost_LIBRARIES}
                          ${SQLITE3_LIBRARIES})
target_include_directories(VFS PUBLIC ${SOURCE_DIR}/include
                               PRIVATE ${SOURCE_DIR}/src)
