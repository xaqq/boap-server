cmake_minimum_required (VERSION 2.6)
project (DetourCrowd)

# Compiler flags
set (CMAKE_CXX_FLAGS "-std=c++11 -W -Wall -g")

include_directories ("Include" "../Detour/Include" "../Recast/Include")

set (SOURCES
	Source/DetourCrowd.cpp
	Source/DetourObstacleAvoidance.cpp
	Source/DetourPathQueue.cpp
	Source/DetourLocalBoundary.cpp
	Source/DetourPathCorridor.cpp
	Source/DetourProximityGrid.cpp
)

add_library(DetourCrowd SHARED ${SOURCES})
