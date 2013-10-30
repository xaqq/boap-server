cmake_minimum_required (VERSION 2.6)
project (default-impl)

# Compiler flags
set (CMAKE_CXX_FLAGS "-std=c++11 -W -Wall -g")

include_directories ("${PROJECT_SOURCE_DIR}/includes" "${PROJECT_SOURCE_DIR}/../includes"
"${PROJECT_SOURCE_DIR}/../logger/logger/includes")

set (SOURCES
  "src/DefaultTcpProtocolHandler.cpp"
  "src/DefaultUdpProtocolHandler.cpp"
  "src/BoapFactory.cpp"
)

add_library(default-impl SHARED ${SOURCES})
