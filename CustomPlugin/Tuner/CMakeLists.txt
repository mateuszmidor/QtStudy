# Find QT dependencies
find_package(Qt5Core REQUIRED)
 	
set(CMAKE_AUTOMOC ON)	
set(CMAKE_INCLUDE_CURRENT_DIR ON)	
 	
 
# Collect sources
set(Tuner_source
        "source/qobject/Tuner.cpp"
        "source/qobject/TunerImpl.cpp"
        "source/qobject/ChannelList.cpp"
        "source/qobject/ChannelListImpl.cpp"
        ${HDR}
        ${INT_HDR}
        ${RESOURCES}
)

# Add library target	
add_library(Tuner ${Tuner_source})
 	
# Add include directories
target_include_directories(Tuner 
                            PUBLIC
                                "source/qobject"
)

# Link target executable with required libs
target_link_libraries(Tuner
                        Qt5::Core
)