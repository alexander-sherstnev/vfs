#############################################################################
# Name:        cmake/wxvfsmanager.cmake
# Purpose:     VFS wxWidgets GUI Manager CMake file
# Author:      Aliaksandr Sharstniou
# Created:     2019-01-12
# Copyright:   (c) 2019 Aliaksandr Sharstniou
# Licence:     MIT
#############################################################################

set(wxWidgets_USE_STATIC ON)
find_package(wxWidgets COMPONENTS core base)
include(${wxWidgets_USE_FILE})

set(WX_VFS_PLUGIN_HDR
        ${SOURCE_DIR}/src/plugins/wxvfsplugin/wxVFSPlugin.h
        ${SOURCE_DIR}/src/plugins/wxvfsplugin/wxVFSApp.h
        ${SOURCE_DIR}/src/plugins/wxvfsplugin/wxVFSFrame.h)

set(WX_VFS_PLUGIN_SRC
        ${SOURCE_DIR}/src/plugins/wxvfsplugin/wxVFSPlugin.cpp
        ${SOURCE_DIR}/src/plugins/wxvfsplugin/wxVFSApp.cpp
        ${SOURCE_DIR}/src/plugins/wxvfsplugin/wxVFSFrame.cpp)

add_library(wxVFSPlugin SHARED ${WX_VFS_PLUGIN_SRC}
                               ${WX_VFS_PLUGIN_HDR})

target_link_libraries(wxVFSPlugin VFS ${wxWidgets_LIBRARIES})
target_include_directories(wxVFSPlugin PUBLIC ${SOURCE_DIR}/include
                                       PRIVATE ${SOURCE_DIR}/src)
