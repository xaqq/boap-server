/* 
 * File:   TcpProtocolHandler.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 9:30 PM
 */

#pragma once
#include "net/ATcpProtocolHandler.hpp"

class AClient;
namespace Net
{
  using boost::asio::ip::tcp;
  class TcpSession;

  class TcpProtocolHandler : public ATcpProtocolHandler
  {
  public:

    TcpProtocolHandler(TcpSession & s);

    virtual ~TcpProtocolHandler() { };

    void bytesAvailable(ByteArray && bytes);
    void start();
    void stop();

  private:
    std::shared_ptr<AClient> client_;
    std::size_t opcode_;
    std::size_t packetSize_;
    std::size_t bytesReceived_;

    void readOpcode(ByteArray && bytes);
    void readSize(ByteArray && bytes);
    void readBody(ByteArray && bytes);

    /**
     * Internal handler called by bytesAvailable.
     */
    std::function<void(ByteArray &&) > handler_;
  };
};

