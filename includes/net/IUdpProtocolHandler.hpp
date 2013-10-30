#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include "ByteArray.hpp"

#pragma once

namespace Net
{
  using boost::asio::ip::tcp;

  class UdpServer;
  class IUdpProtocolHandler
  {
  public:

    IUdpProtocolHandler(UdpServer &) { };

    virtual ~IUdpProtocolHandler() { };
    /**
     * This method is called by the socket when datagram are available
     * 
     * @param bytes ByteArray you requested; Those data are your responsability now;
     */
    virtual void bytesAvailable(ByteArray && bytes, boost::asio::ip::udp::endpoint e) = 0;
  };
};
