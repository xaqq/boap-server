cmake_minimum_required (VERSION 2.6)
project (libbehavior)

# Compiler flags
set (CMAKE_CXX_FLAGS "-std=c++11 -W -Wall -g -fpermissive")

include_directories ("includes")

set (SOURCES
	src/CountLimitNode.cpp 
 src/FPCompare.cpp  
src/mtrand.cpp  
src/ParallelNode.cpp  
src/PriorityNode.cpp  
src/ProbabilityNode.cpp  
src/RepeatNode.cpp  
src/SequentialNode.cpp
src/NoClassSpec.cpp
)

add_library(libbehavior SHARED ${SOURCES})
