#include <boost/asio.hpp>
#include <thread>
#include <memory>
#include "net/TcpServer.hpp"
#include "net/UdpServer.hpp"
#include "Log.hpp"
#include "Server.hpp"
#include "Scheduler.hpp"

void start_tcp(boost::asio::io_service *tcp_io_service)
{
  tcp_io_service->run();
}

void start_udp(boost::asio::io_service *udp_io_service)
{
  udp_io_service->run();
}

void start_gameserver(Server *server)
{
  server->run();
}

int main(int, char**)
{
  try
    {
      Log::defaultConfig();
      Scheduler *sched = Scheduler::instance();
      Server server;

      sched->setServer(&server);

      boost::asio::io_service tcp_io_service;
      Net::TcpServer tcpServer(tcp_io_service, 4242);
      sched->setTcp(&tcpServer);


      boost::asio::io_service udp_io_service;
      Net::UdpServer udpServer(udp_io_service, 4242);

      sched->setUdp(&udpServer);

      boost::asio::io_service sig_io_service;
      boost::asio::signal_set signals(sig_io_service);
      signals.add(SIGINT);
      signals.async_wait(std::bind(&Net::TcpServer::stop, &tcpServer));
      signals.async_wait(std::bind(&Net::UdpServer::stop, &udpServer));
      signals.async_wait(std::bind(&Server::stop, &server));

      std::thread tcpThread(start_tcp, &tcp_io_service);
      std::thread udpThread(start_udp, &udp_io_service);
      std::thread gameServerThread(start_gameserver, &server);
      sig_io_service.run();
      tcpThread.join();
      udpThread.join();
      gameServerThread.join();
      delete sched;
    }
  catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << std::endl;
    }

  return 0;
}
