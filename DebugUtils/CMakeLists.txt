cmake_minimum_required (VERSION 2.6)
project (DebugUtils)

# Compiler flags
set (CMAKE_CXX_FLAGS "-std=c++11 -W -Wall -g")

include_directories ("Include" "../Detour/Include" "../Recast/Include"
		    "../DetourTileCache/Include")

set (SOURCES
Source/DebugDraw.cpp
Source/RecastDebugDraw.cpp
Source/DetourDebugDraw.cpp
Source/RecastDump.cpp
)

add_library(DebugUtils SHARED ${SOURCES})
