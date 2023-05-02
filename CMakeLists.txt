cmake_minimum_required(VERSION 3.24)
project(finalproj_spatialkeyframing_sp23_cs184)

set(CMAKE_CXX_STANDARD 17)

add_executable(finalproj_spatialkeyframing_sp23_cs184 main.cpp SpatialKeyframing.h SpatialKeyframing.cpp RadialBasisFunction.h RadialBasisFunction.cpp Gauss.h)

set(OGRE_INCLUDE_DIR "/Users/armaangoel/Desktop/184/finalproj-spatialkeyframing/ogre-13.6.4/OgremMain/include")
set(OGRE_LIBRARY_DIR "/Users/armaangoel/Desktop/184/finalproj-spatialkeyframing/ogre-13.6.4/build/lib")

include_directories(${OGRE_INCLUDE_DIR})
link_directories(${OGRE_LIBRARY_DIR})

target_link_libraries(finalproj_spatialkeyframing_sp23_cs184 OgreMain OgreOverlay OgreRTShaderSystem)
