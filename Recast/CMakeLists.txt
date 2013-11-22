cmake_minimum_required (VERSION 2.6)
project (Recast)

# Compiler flags
set (CMAKE_CXX_FLAGS "-std=c++11 -W -Wall -g")

include_directories ("Include")

set (SOURCES
Source/RecastAlloc.cpp
Source/RecastLayers.cpp
Source/RecastArea.cpp
Source/RecastMesh.cpp
Source/RecastContour.cpp
Source/RecastMeshDetail.cpp
Source/Recast.cpp
Source/RecastRasterization.cpp
Source/RecastFilter.cpp
Source/RecastRegion.cpp
)

add_library(Recast SHARED ${SOURCES})
