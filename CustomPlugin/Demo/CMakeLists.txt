# Find QT dependencies
find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Qml REQUIRED)
 	
set(CMAKE_AUTOMOC ON)	
set(CMAKE_INCLUDE_CURRENT_DIR ON)	
 	
# Add your resources here	
qt5_add_resources(RESOURCES
                    "resource/qml.qrc"
)
 
# Collect sources
set(Demo_source
        "source/main.cpp"
        ${HDR}
        ${INT_HDR}
        ${RESOURCES}
)

# Add executable target	
add_executable(Demo ${Demo_source})
 	
# Add include directories
target_include_directories(Demo 
                            PUBLIC
                                "source"
)

# Link target executable with required libs
target_link_libraries(Demo
                        Qt5::Core
                        Qt5::Quick
                        Qt5::Qml
)

install(TARGETS Demo
         DESTINATION ${BUILD_OUTPUT_DIR}
)