#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include "ByteArray.hpp"

#pragma once

namespace Net
{
  using boost::asio::ip::tcp;

  class IUdpProtocolHandler
  {
  public:

    IUdpProtocolHandler() {};

    virtual ~IUdpProtocolHandler() {};
    /**
     * This method is called by the socket when the data you requested are available;
     * 
     * @param bytes ByteArray you requested; Those data are your responsability now;
     */
    virtual void bytesAvailable(ByteArray && bytes, std::pair<unsigned short, std::string>) = 0;
  };
};
