#include <boost/asio.hpp>
#include <thread>
#include <functional>
#include <memory>
#include "net/TcpServer.hpp"
#include "net/UdpServer.hpp"
#include "Log.hpp"
#include "LogMgr.hpp"
#include "Server.hpp"
#include "Scheduler.hpp"
#include "BoapFactory.hpp"
#include "sql/SqlHandler.hpp"

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

void start_sql(SqlHandler *h)
{
  h->run();
}

void logConfig()
{
  using namespace Log;
  std::shared_ptr<ALogger> stdoutLogger(new StdoutLogger(new SimpleFormatter()));
  std::shared_ptr<ALogger> stderrLogger(new StderrLogger(new DefaultFormatter()));

  std::shared_ptr<IFilter> stdoutFilter(new DefaultFilter({LogLevel::DEBUG, LogLevel::INFO}));
  std::shared_ptr<IFilter> stderrFilter(new DefaultFilter({LogLevel::WARN, LogLevel::ERROR}));

  stdoutLogger->registerFilter(stdoutFilter);
  stderrLogger->registerFilter(stderrFilter);
  LogMgr::registerLogger("stdout", stdoutLogger);
  LogMgr::registerLogger("stderr", stderrLogger);

  /* Linux syslog facility */
#ifdef __gnu_linux__
  std::shared_ptr<ALogger> syslogLogger(new SyslogLogger(new DefaultFormatter()));
  std::shared_ptr<IFilter> syslogFilter(new DefaultFilter(LogLevel::ERROR));
  syslogLogger->registerFilter(syslogFilter);
  LogMgr::registerLogger("syslog", syslogLogger);
#endif
}

namespace Net
{
  class ATcpProtocolHandler;
};

int main(int, char**)
{
  try
    {
      logConfig();
      Scheduler *sched = Scheduler::instance();
      SqlHandler sql; 
      Server &server = Server::instance();
      sched->setSql(&sql);
      sched->setServer(&server);

      boost::asio::io_service tcp_io_service;
      Net::TcpServer tcpServer(tcp_io_service, 4242, &BoapFactory::createTcpProtocolHandler);
      Net::TcpServer tcpServer2(tcp_io_service, 4243, &BoapFactory::createTcpAdminProtocolHandler);
      sched->setTcp(&tcpServer);

      
      boost::asio::io_service udp_io_service;
      Net::UdpServer udpServer(udp_io_service, 4242, &BoapFactory::createUdpProtocolHandler);

      sched->setUdp(&udpServer);

      boost::asio::io_service sig_io_service;
      boost::asio::signal_set signals(sig_io_service);
      signals.add(SIGINT);
      signals.async_wait(std::bind(&Net::TcpServer::stop, &tcpServer));
      signals.async_wait(std::bind(&Net::UdpServer::stop, &udpServer));
      signals.async_wait(std::bind(&Server::stop, &server));
      signals.async_wait(std::bind(&SqlHandler::stop, &sql));

      std::thread sqlThread(start_sql, &sql);
      std::thread tcpThread(start_tcp, &tcp_io_service);
      std::thread udpThread(start_udp, &udp_io_service);
      std::thread gameServerThread(start_gameserver, &server);
      sig_io_service.run();
      tcpThread.join();
      udpThread.join();
      gameServerThread.join();
      sqlThread.join();
      delete &server;
      delete sched;
    }
  catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << std::endl;
    }

  return 0;
}
