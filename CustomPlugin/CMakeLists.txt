cmake_minimum_required (VERSION 3.2)
project (CustomPlugin)

set(PROJECT_MAJOR_VERSION 0)
set(PROJECT_MINOR_VERSION 1)
set(PROJECT_PATCH_LEVEL 0)

set(PROJECT_VERSION ${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}.${PROJECT_PATCH_LEVEL})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -std=c++11 -m64 -fPIC")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

# set output directory for "make install"
set (BUILD_OUTPUT_DIR "${PROJECT_BINARY_DIR}/CustomPluginBuild") 

# dont strip RPATH; needed for the libPlugin.so to find QT libs
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# subprojects
add_subdirectory(Tuner)
add_subdirectory(Plugin)
add_subdirectory(Demo)

# "make install" rules provided in subprojects