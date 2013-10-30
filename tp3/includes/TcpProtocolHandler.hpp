/* 
 * File:   TcpProtocolHandler.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 9:30 PM
 */

#pragma once

#include "net/DefaultTcpProtocolHandler.hpp"

namespace Net
{
  using boost::asio::ip::tcp;

  class TcpSession;

  class TcpProtocolHandler : public DefaultTcpProtocolHandler
  {
  public:

    TcpProtocolHandler(TcpSession & s);

    virtual ~TcpProtocolHandler() { };

    void bytesAvailable(ByteArray && bytes);
    void start();
    void stop();
    
  private:
    std::size_t bytesReceived_;
  };
};

