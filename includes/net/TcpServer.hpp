#include <boost/asio.hpp>

#pragma once

namespace Net
{

  class TcpServer
  {
  public:

    TcpServer(boost::asio::io_service& io_service, short port);
    ~TcpServer();

    /**
     * Called by signal handler when receiving SIGINT
     */
    void stop();
    
    boost::asio::io_service &ioService();

  private:
    void do_accept();
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;

  };
};
