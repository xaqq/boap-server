/* 
 * File:   TcpProtocolHandler.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 9:30 PM
 */

#pragma once
#include "net/ATcpProtocolHandler.hpp"
#include <memory>
#include <cstdint>

class Client;
namespace Net
{
  using boost::asio::ip::tcp;
  class TcpSession;

  class TcpProtocolHandler : public ATcpProtocolHandler, public std::enable_shared_from_this<ATcpProtocolHandler>
  {
  public:

    TcpProtocolHandler();

    virtual ~TcpProtocolHandler() { };

    void bytesAvailable(ByteArray bytes) override;
    void start();
    void stop();

    virtual void disconnected() override;

  private:
    std::shared_ptr<Client> client_;
    std::uint16_t opcode_;
    std::uint16_t packetSize_;
    std::size_t bytesReceived_;

    void readOpcode(ByteArray bytes);
    void readSize(ByteArray bytes);
    void readBody(ByteArray bytes);

    /**
     * Internal handler called by bytesAvailable.
     */
    std::function<void(ByteArray &&) > handler_;
  };
};

