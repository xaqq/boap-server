cmake_minimum_required (VERSION 2.6)
project (DetourTileCache)

# Compiler flags
set (CMAKE_CXX_FLAGS "-std=c++11 -W -Wall -g")

include_directories ("Include" "../Detour/Include")

set (SOURCES
	Source/DetourTileCacheBuilder.cpp  
	Source/DetourTileCache.cpp
)

add_library(DetourTileCache SHARED ${SOURCES})
