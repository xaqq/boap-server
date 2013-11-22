cmake_minimum_required (VERSION 2.6)
project (boapd)

find_package(Bullet REQUIRED)
find_package(Protobuf REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

add_definitions("-g -W -Wall -std=c++11")

add_subdirectory("protobuf")
add_subdirectory("logger/logger")
#add_subdirectory("tp3")
add_subdirectory("Recast")
add_subdirectory("Detour")
add_subdirectory("DetourTileCache")
add_subdirectory("DebugUtils")
add_subdirectory("DetourCrowd")

set(SOURCES 
##Packets
src/packets/HelloPacket.cpp
src/packets/CMSGAuthPacket.cpp
src/packets/CMSGCreateGame.cpp
src/packets/CMSGGameList.cpp
src/packets/CMSGJoinGame.cpp
src/packets/CMSGUdpAuth.cpp
src/packets/APacket.cpp
##Factories
src/BoapFactory.cpp
src/packets/PacketFactory.cpp
##Protocol handlers
src/net/ATcpProtocolHandler.cpp
src/net/AUdpProtocolHandler.cpp
src/net/TcpServer.cpp
src/net/UdpServer.cpp
src/net/TcpSession.cpp
src/net/TcpProtocolHandler.cpp
src/net/UdpProtocolHandler.cpp
src/net/AdminTcpHandler.cpp
##Packet Handlers
src/handlers/AuthPacketHandler.cpp
src/handlers/CreateGameHandler.cpp
src/handlers/GameListHandler.cpp
src/handlers/HelloPacketHandler.cpp
src/handlers/UdpAuthHandler.cpp
src/handlers/APacketHandler.cpp

src/main.cpp
src/world/Game.cpp
src/Uuid.cpp
src/ByteArray.cpp
            src/world/World.cpp
src/sql/SqlHandler.cpp
src/sql/EntityTemplate.cpp
src/world/GameEntity.cpp
            src/Clock.cpp
            src/Server.cpp
            src/AClient.cpp
            src/Scheduler.cpp
            src/SafeQueue.cpp
src/world/RecastConverter.cpp
src/world/EntityFactory.cpp
src/sql/ShapeTemplate.cpp
src/world/NavMeshBuilder.cpp
src/world/InputGeom.cpp
src/world/MeshLoaderObj.cpp
src/world/ChunkyTriMesh.cpp
src/world/PathFindHelper.cpp
src/world/MovableEntity.cpp
)

include_directories(${Boost_INCLUDE_DIRS} ${PROTOBUF_INCLUDE_DIRS} ${BULLET_INCLUDE_DIRS}
"includes" "logger/logger/includes" "Recast/Include" "Detour/Include" "DebugUtils/Include" "DetourTileCache/Include"
"DetourCrowd/Include")


add_executable(boapd ${SOURCES})
target_link_libraries( boapd ${Boost_LIBRARIES} mysqlcppconn Logger BulletDynamics Detour Recast DebugUtils DetourTileCache DetourCrowd boapd-protobuf)
