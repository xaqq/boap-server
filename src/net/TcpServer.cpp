#include "net/TcpServer.hpp"
#include "net/TcpSession.hpp"
#include "Log.hpp"
#include <memory>

using namespace Net;

TcpServer::TcpServer(boost::asio::io_service& io_service, short port, TcpHandlerFactory handlerFactory)
: handlerFactory_(handlerFactory),
acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
socket_(io_service)
{
  do_accept();
}

TcpServer::~TcpServer()
{
  INFO("TcpServer deleted");
}

void TcpServer::do_accept()
{

  acceptor_.async_accept(socket_,
                         [this](boost::system::error_code ec)
  {
                         if (!ec)
      {
                         std::make_shared<TcpSession > (std::move(socket_), handlerFactory_())->start();
      }
    else
      {
                         ERROR("ACCEPT ERROR: " << ec.message());
      }
                         do_accept();
  });
}

void TcpServer::stop()
{
  INFO("Stopping TCP server...");
  acceptor_.get_io_service().stop();
}

boost::asio::io_service &TcpServer::ioService()
{
  return socket_.get_io_service();
}
