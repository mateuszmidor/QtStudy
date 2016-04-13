cmake_minimum_required (VERSION 2.8)

# Executable name 
project (CMakeIntegration)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Qml REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Add your resources here
qt5_add_resources(RESOURCES 
                        qml.qrc)

# Add your source files here
add_executable( ${PROJECT_NAME} 
                main.cpp 
                ${HDR} 
                ${INT_HDR} 
                ${RESOURCES} )

target_link_libraries( ${PROJECT_NAME} 
                        Qt5::Widgets 
                        Qt5::Core 
                        Qt5::Qml)
