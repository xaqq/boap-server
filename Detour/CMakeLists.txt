cmake_minimum_required (VERSION 2.6)
project (Detour)

# Compiler flags
set (CMAKE_CXX_FLAGS "-std=c++11 -W -Wall -g")

include_directories ("Include")

set (SOURCES
	Source/DetourAlloc.cpp
	Source/DetourNavMeshBuilder.cpp
	Source/DetourNavMeshQuery.cpp
	Source/DetourCommon.cpp
	Source/DetourNavMesh.cpp
	Source/DetourNode.cpp
)

add_library(Detour SHARED ${SOURCES})
