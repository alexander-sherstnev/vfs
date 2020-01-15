#############################################################################
# Name:        CMakeLists.txt
# Purpose:     Primary CMake for VFS
# Author:      Aliaksandr Sharstniou
# Created:     2019-01-12
# Copyright:   (c) 2019 Aliaksandr Sharstniou
# Licence:     MIT
#############################################################################

cmake_minimum_required(VERSION 3.13)

project(VFS VERSION 1.0.0
        DESCRIPTION "Virtual File System"
        LANGUAGES CXX)

# Initialize global variables
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${SOURCE_DIR}/cmake/modules/)


set(BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_DIR ${BINARY_DIR}/lib)

include(cmake/main.cmake)
