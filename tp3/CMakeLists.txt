cmake_minimum_required (VERSION 2.6)
project (tp3)

# Compiler flags
set (CMAKE_CXX_FLAGS "-std=c++11 -W -Wall -g")
find_package(Boost COMPONENTS system REQUIRED)
include_directories ("${PROJECT_SOURCE_DIR}/includes" "${PROJECT_SOURCE_DIR}/../includes"
"${PROJECT_SOURCE_DIR}/../logger/logger/includes"
"${PROJECT_SOURCE_DIR}/../default-impl/includes"
"${PROJECT_SOURCE_DIR}/../Recast/Include"
"${PROJECT_SOURCE_DIR}/../Detour/Include"
"/usr/include/bullet"
${Boost_INCLUDE_DIRS} )

set (SOURCES
  "src/TcpProtocolHandler.cpp"
  "src/AdminTcpHandler.cpp"
  "src/UdpProtocolHandler.cpp"
  "src/BoapFactory.cpp"
  "src/Client.cpp"
  "src/HelloPacketHandler.cpp"
  "src/UdpAuthHandler.cpp"
  "src/HelloPacket.cpp"
  "src/UdpAuthPacket.cpp"
  "src/MotdPacket.cpp"
  "src/PacketFactory.cpp"
  "src/CMSGAuthPacket.cpp"
   "src/AuthPacketHandler.cpp"
"src/AuthTask.cpp"
"src/SMSGUdpCode.cpp"
"src/CMSGCreateGame.cpp"
"src/SMSGCreateGame.cpp"
"src/SMSGAuth.cpp"
"src/CMSGGameList.cpp"
"src/SMSGGameList.cpp"
"src/GameListHandler.cpp"
"src/CreateGameHandler.cpp"
)

target_link_libraries(${Boost_LIBRARIES})
add_library(tp3 SHARED ${SOURCES})

