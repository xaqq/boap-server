#include "net/TcpServer.hpp"
#include "net/TcpSession.hpp"
#include "Log.hpp"
#include <memory>

using namespace Net;

void TcpServer::do_accept()
{

  acceptor_.async_accept(socket_,
                         [this](boost::system::error_code ec)
  {
                         if (!ec)
      {
                         std::make_shared<TcpSession > (std::move(socket_))->start();
      }
                         do_accept();
  });
}

void TcpServer::stop()
{
  INFO("Stopping server...");
  acceptor_.get_io_service().stop();
}
