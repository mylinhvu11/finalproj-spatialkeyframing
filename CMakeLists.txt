cmake_minimum_required(VERSION 3.24)
project(finalproj_spatialkeyframing_sp23_cs184)

set(CMAKE_CXX_STANDARD 17)

add_executable(finalproj_spatialkeyframing_sp23_cs184 main.cpp SpatialKeyframing.h SpatialKeyframing.cpp RadialBasisFunction.h RadialBasisFunction.cpp Gauss.h Ogre.h ogre-13.6.4/OgreMain/src/OgreStableHeaders.h ogre-13.6.4/build/include/OgreBuildSettings.h)

set(OGRE_INCLUDE_DIR "../ogre-13.6.4/OgreMain/build/include")
set(OGRE_LIBRARY_DIR "../ogre-13.6.4/build/")

configure_file("ogre-13.6.4/CMake/Templates/OgreBuildSettings.h.in"
        "${CMAKE_CURRENT_BINARY_DIR}/../build/include/OgreBuildSettings.h" @ONLY)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
include_directories(${OGRE_INCLUDE_DIR})

link_directories(${OGRE_LIBRARY_DIR})

target_link_libraries(finalproj_spatialkeyframing_sp23_cs184 OgreMain OgreOverlay OgreRTShaderSystem)
