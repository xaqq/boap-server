/* 
 * File:   UdpServer.cpp
 * Author: xaqq
 * 
 * Created on October 29, 2013, 7:40 PM
 */

#include "net/UdpServer.hpp"
#include "Log.hpp"
#include "BoapFactory.hpp"
using namespace Net;
using namespace boost::asio::ip;

UdpServer::UdpServer(boost::asio::io_service& io_service, short port) :
socket_(io_service, udp::endpoint(udp::v4(), port)),
buffer_(PACKET_MAX_SIZE),
protocolHandler_(BoapFactory::createUdpProtocolHandler())
{
  start_receive();
}

UdpServer::~UdpServer()
{
  INFO("UdpServer deleted");
}

void UdpServer::stop()
{
  INFO("Stopping UDP server...");
  socket_.get_io_service().stop();
}

void UdpServer::start_receive()
{

  socket_.async_receive_from(
                             boost::asio::buffer(buffer_), remoteEndpoint_,
                             [this](boost::system::error_code ec,
                                    std::size_t bytes)
  {
                             protocolHandler_->bytesAvailable(std::move(buffer_),
                                                              std::make_pair(remoteEndpoint_.port(),
                                                                             remoteEndpoint_.address().to_string()));
                             buffer_.resize(PACKET_MAX_SIZE);
                             start_receive();
  });
}
