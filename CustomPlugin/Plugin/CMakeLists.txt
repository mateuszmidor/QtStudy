# Find QT dependencies
find_package(Qt5Core REQUIRED)
 	
set(CMAKE_AUTOMOC ON)	
set(CMAKE_INCLUDE_CURRENT_DIR ON)	
 	
 
# Collect sources
set(Plugin_source
    "source/Plugin.cpp"
)

# Add executable target	
add_library(Plugin SHARED ${Plugin_source})
 	
# Add include directories
target_include_directories(Plugin 
                            PUBLIC
                                "source"
)

# Link target executable with required libs
target_link_libraries(Plugin
                        Tuner
                        Qt5::Core
)

install(TARGETS Plugin
        DESTINATION ${BUILD_OUTPUT_DIR}/Plugin
)

install(FILES qmldir
        DESTINATION ${BUILD_OUTPUT_DIR}/Plugin
)