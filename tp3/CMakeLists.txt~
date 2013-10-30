cmake_minimum_required (VERSION 2.6)
project (Logger)

# Compiler flags
set (CMAKE_CXX_FLAGS "-std=c++11 -W -Wall -g")

include_directories ("${PROJECT_SOURCE_DIR}/includes")

set (SOURCES
  "src/ALogger.cpp"
  "src/DefaultFilter.cpp"
  "src/AFormatter.cpp"
  "src/DefaultFormatter.cpp"
  "src/LogMgr.cpp"
  "src/StdoutLogger.cpp"
  "src/StderrLogger.cpp"
  "src/Log.cpp"
)

# Linux specific sources
IF (UNIX)
  set (SOURCES "${SOURCES}"
    "src/SyslogLogger.cpp")
endif(UNIX)

add_library(Logger SHARED ${SOURCES})
