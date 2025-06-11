cmake_minimum_required(VERSION 3.10.0)
project(flora VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add cpm.cmake for dependency management
include(FetchContent)

file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
)

include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

CPMAddPackage(
  NAME material-color-utilities-cpp
  GITHUB_REPOSITORY Blessing-You/material-color-utilities-cpp
  GIT_TAG main
)

add_subdirectory(libs/stb_image)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

add_library(flora ${SOURCES})

target_link_libraries(flora PUBLIC 
    material-color-utilities-cpp
    stb_image
)

target_include_directories(flora PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)