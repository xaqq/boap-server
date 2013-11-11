cmake_minimum_required (VERSION 2.6)
project (tp3)

# Compiler flags
set (CMAKE_CXX_FLAGS "-std=c++11 -W -Wall -g")

include_directories ("${PROJECT_SOURCE_DIR}/includes" "${PROJECT_SOURCE_DIR}/../includes"
"${PROJECT_SOURCE_DIR}/../logger/logger/includes"
"${PROJECT_SOURCE_DIR}/../default-impl/includes")

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
)

add_library(tp3 SHARED ${SOURCES})
