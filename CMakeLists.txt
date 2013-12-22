cmake_minimum_required (VERSION 2.6)
project (boapd)

include(ODB.cmake)

find_package(Bullet REQUIRED)
find_package(Protobuf REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

set(Bullet_LIBRARIES
${BULLET_COLLISION_LIBRARY}
${BULLET_DYNAMICS_LIBRARY}
${BULLET_SOFTBODY_LIBRARY}
LinearMath
)

set(ODB_INCLUDE_DIRS
${CMAKE_CURRENT_SOURCE_DIR}/odb/libodb-mysql-2.3.0
${CMAKE_CURRENT_SOURCE_DIR}/odb/libodb-2.3.0
${CMAKE_CURRENT_SOURCE_DIR}/odb/odb-2.3.0
)

# ODB libraries
LINK_DIRECTORIES( 
${CMAKE_CURRENT_SOURCE_DIR}/odb/libodb-2.3.0/odb/.libs
${CMAKE_CURRENT_SOURCE_DIR}/odb/libodb-mysql-2.3.0/odb/mysql/.libs
)

add_definitions("-g -W -Wall -std=c++11 -Wunknown-pragmas")
add_subdirectory("protobuf")
add_subdirectory("logger/logger")
add_subdirectory("Recast")
add_subdirectory("Detour")
add_subdirectory("DetourTileCache")
add_subdirectory("DebugUtils")
add_subdirectory("DetourCrowd")
add_subdirectory("libbehavior")

set(SOURCES 
##Packets
src/packets/HelloPacket.cpp
src/packets/CMSGAuthPacket.cpp
src/packets/CMSGCreateGame.cpp
src/packets/CMSGGameList.cpp
src/packets/CMSGJoinGame.cpp
src/packets/CMSGUdpAuth.cpp
src/packets/SMSGAuth.cpp
src/packets/SMSGCreateGame.cpp
src/packets/SMSGGameList.cpp
src/packets/SMSGUdpCode.cpp
src/packets/APacket.cpp

##Factories
src/BoapFactory.cpp
src/packets/PacketFactory.cpp
src/world/EntityFactory.cpp

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
src/handlers/JoinGameHandler.cpp
src/handlers/GamePacketHandler.cpp
src/handlers/APacketHandler.cpp

##Clients
src/AClient.cpp
src/Client.cpp

src/AuthTask.cpp
src/main.cpp

##World / game stuff
src/world/World.cpp
src/world/Game.cpp
src/world/GameEntity.cpp
src/world/MovementComponent.cpp
src/world/RecastConverter.cpp
src/world/NavMeshBuilder.cpp
src/world/InputGeom.cpp
src/world/MeshLoaderObj.cpp
src/world/ChunkyTriMesh.cpp
src/world/PathFindHelper.cpp
src/world/MovableEntity.cpp
src/world/ResourceEntity.cpp
src/world/ResourceCollectorEntity.cpp
src/world/PathFindResult.cpp

src/world/WorldObject.cpp

##Utils
src/Uuid.cpp
src/ByteArray.cpp
src/Clock.cpp
src/Scheduler.cpp
src/SafeQueue.cpp
src/ATask.cpp

## Sql
src/sql/SqlHandler.cpp
src/sql/EntityTemplate.cpp
src/sql/ShapeTemplate.cpp

## Server
src/Server.cpp

## Exceptions
src/exceptions/WorldFailedInit.cpp

## Observer
src/observers/AMainThreadGameObserver.cpp

## Behavior
src/behaviors/Behavior.cpp
src/behaviors/Speak.cpp
src/behaviors/Move.cpp
src/behaviors/MoveToDestination.cpp
src/behaviors/FindNearestResource.cpp
src/behaviors/CollectResource.cpp
src/behaviors/CooldownDecorator.cpp

## Colliders
src/colliders/ACollider.cpp

## Init scripts
src/world/initscript/GameObjectInit.cpp

## DB 
src/db/DBManager.cpp

## ODB Generated code
odb_gen/Account_odb.cpp
)

set(ODB_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/includes/db/Account.hpp)
odb_compile(HEADER ${ODB_HEADERS}
  OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/odb_gen
  INCLUDE ${ODB_INCLUDE_DIRS}
  DB mysql
  STANDARD c++11
  GENERATE_QUERY
  GENERATE_SCHEMA)

include_directories(${Boost_INCLUDE_DIRS} ${PROTOBUF_INCLUDE_DIRS} ${BULLET_INCLUDE_DIRS}
"includes" "logger/logger/includes" "Recast/Include" "Detour/Include" "DebugUtils/Include" "DetourTileCache/Include"
"DetourCrowd/Include" "libbehavior/includes" "protobuf"
"includes/db"
${ODB_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}
)


add_executable(boapd ${SOURCES})
target_link_libraries( boapd Logger Detour Recast DebugUtils DetourTileCache DetourCrowd libbehavior boapd-protobuf ${Bullet_LIBRARIES} ${Boost_LIBRARIES} mysqlcppconn mysqlclient pthread odb odb-mysql )
