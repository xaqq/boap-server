#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include <queue>
#include "ByteArray.hpp"

#pragma once

namespace Net
{
  using boost::asio::ip::tcp;
  class ITcpProtocolHandler;
  class TcpSession : public std::enable_shared_from_this<TcpSession>
  {
  public:
    TcpSession(tcp::socket socket);
    ~TcpSession();
    /**
     * Called by the server when ready
     */
    void start();
    
    /**
     * Called by the server when stopped
     * @param bytes
     */
    void stop();
    
    /**
     * Called by ProtocolHandler implemented to request some data.
     * When thoses are available, the socket will notify the ProtocolHandler.
     * 
     * request() IS NOT THREAD SAFE.
     * @param bytes
     */
    void request(std::size_t bytes);


    /**
     * This method will be thread safe;
     * @param b
     */
    void post(ByteArray && b);

  private:
    void do_read();
    void do_write();
    tcp::socket socket_;

    /**
     * Read buffer; We build a new buffer each time a request()
     */
    std::queue<ByteArray> readBuffers_;

    std::shared_ptr<ITcpProtocolHandler> protocolHandler_;

    // TODO: Need thread safe queue
    std::queue<ByteArray> packetQueue_;
    bool writing_;
    bool reading_;
  };
};

