cmake_minimum_required (VERSION 2.6)
project (boapd-protobuf)

find_package(Protobuf REQUIRED)

add_definitions("-g -W -Wall -std=c++11")
PROTOBUF_GENERATE_CPP (PROTO_SRCS PROTO_HRDS 
CMSGAuth.proto SMSGAuth.proto
CMSGCreateGame.proto
SMSGCreateGame.proto
SMSGGameList.proto
CMSGJoinGame.proto
)

add_library(boapd-protobuf ${PROTO_SRCS} ${PROTO_HRDS})
target_link_libraries(boapd-protobuf protobuf)
