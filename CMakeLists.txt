cmake_minimum_required (VERSION 2.6)
project (boapd)

add_definitions("-g -W -Wall -std=c++11")
add_subdirectory("logger/logger")
add_subdirectory("tp3")

#link_directories("logger/logger")
set(SOURCES src/main.cpp
            src/net/ATcpProtocolHandler.cpp
            src/net/AUdpProtocolHandler.cpp
	    src/net/TcpServer.cpp
	    src/net/TcpSession.cpp
            src/net/UdpServer.cpp
            src/world/World.cpp
src/sql/SqlHandler.cpp
src/sql/EntityTemplate.cpp
src/world/GameEntity.cpp
            src/Clock.cpp
            src/Server.cpp
            src/AClient.cpp
            src/Scheduler.cpp
            src/SafeQueue.cpp
            src/APacket.cpp
            src/APacketHandler.cpp
)

find_package(Boost COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} "includes" "logger/logger/includes" "/usr/include/bullet")


add_executable(boapd ${SOURCES})
target_link_libraries( boapd ${Boost_LIBRARIES} mysqlcppconn Logger tp3 BulletDynamics)
