cmake_minimum_required (VERSION 2.6)
project (boapd)

add_definitions("-g -W -Wall -std=c++11")

set(SOURCES src/main.cpp
	    src/net/TcpServer.cpp
	    src/net/TcpSession.cpp
            src/net/IProtocolHandler.cpp
	    src/net/ProtocolHandler.cpp)

find_package(Boost COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} "includes")


add_executable(boapd ${SOURCES})
target_link_libraries( boapd ${Boost_LIBRARIES} )
