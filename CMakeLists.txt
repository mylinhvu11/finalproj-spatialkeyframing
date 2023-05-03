cmake_minimum_required(VERSION 3.24)
project(finalproj-spatialkeyframing)

set(CMAKE_CXX_STANDARD 17)

# Set the architecture to build for
set(CMAKE_OSX_ARCHITECTURES "arm64")

#set(OGRE_INCLUDE_DIR "../ogre-13.6.4/build/include")
#set(OGRE_LIBRARY_DIR "../ogre-13.6.4/build/")

include_directories(${OGRE_INCLUDE_DIRS})
include_directories(ogre-13.6.4/build/include)
link_directories(${OGRE_LIBRARY_DIRS})

#configure_file("ogre-13.6.4/CMake/Templates/OgreBuildSettings.h.in"
#        "${CMAKE_CURRENT_BINARY_DIR}/../build/include/OgreBuildSettings.h" @ONLY)

#include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
#include_directories(${OGRE_INCLUDE_DIR})

#link_directories(${OGRE_LIBRARY_DIR})
add_executable(finalproj-spatialkeyframing main.cpp)

target_link_libraries(finalproj-spatialkeyframing ${OGRE_LIBRARIES})

