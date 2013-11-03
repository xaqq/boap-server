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

    IUdpProtocolHandler(UdpServer &, boost::asio::ip::udp::endpoint) { };

    virtual ~IUdpProtocolHandler() { };
    /**
     * This method is called by the socket when datagram are available
     * 
     * @param bytes ByteArray you requested; Those data are your responsability now;
     */
    virtual void bytesAvailable(ByteArray && bytes) = 0;
    virtual boost::asio::ip::udp::endpoint &endpoint() = 0;
    virtual const boost::asio::ip::udp::endpoint &endpoint() const = 0;

    /**
     * @return timestamp of last activity -- used to expire handler;
     */
    virtual time_t lastActivity() const = 0;
    /**
     * Set last activity timestamp;
     * @param 
     */
    virtual void lastActivity(time_t) = 0;
  };
};
