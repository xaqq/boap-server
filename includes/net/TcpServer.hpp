#pragma once
#include <functional>
#include <boost/asio.hpp>
#include "Network.hpp"

namespace Net
{
  class TcpServer
  {
  public:
    TcpServer(boost::asio::io_service& io_service, short port, TcpHandlerFactory factory);
    ~TcpServer();

    /**
     * Called by signal handler when receiving SIGINT
     */
    void stop();

    boost::asio::io_service &ioService();

  private:
    void do_accept();
    
    /**
     * Functor that create a new ATcpProtocolHandler. It is passed to the TcpSession which use
     * it internally.
     */
    TcpHandlerFactory handlerFactory_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;

  };
};
