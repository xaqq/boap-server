#include <boost/asio.hpp>
#include <thread>
#include <functional>
#include <memory>
#include <stdexcept>
#include <exception>
#include "net/TcpServer.hpp"
#include "net/UdpServer.hpp"
#include "Log.hpp"
#include "LogMgr.hpp"
#include "Server.hpp"
#include "Scheduler.hpp"
#include "BoapFactory.hpp"
#include "sql/SqlHandler.hpp"
#include "db/DBManager.hpp"


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
#ifndef NO_LOG
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
#endif
}

namespace Net
{
    class ATcpProtocolHandler;
};

int main(int, char**)
{
    std::thread sqlThread;
    std::thread tcpThread;
    std::thread udpThread;
    std::thread gameServerThread;

    try
    {
        logConfig(); // logger configuration.
        DB::DBManager::instance(); // start mysql connection pool.
        Scheduler *sched = Scheduler::instance();
        SqlHandler sql;
        sched->setSql(&sql);
        // fire-up sql asap; it will be required by server initialisation code
        sqlThread = std::thread(start_sql, &sql);

        std::shared_ptr<Server> server(&Server::instance());
        sched->setServer(server.get());
        boost::asio::io_service tcp_io_service;
        Net::TcpServer tcpServer(tcp_io_service, 4242, &BoapFactory::createTcpProtocolHandler);
        // Net::TcpServer tcpServer2(tcp_io_service, 4243, &BoapFactory::createTcpAdminProtocolHandler);

        sched->setTcp(&tcpServer);

        boost::asio::io_service udp_io_service;
        Net::UdpServer udpServer(udp_io_service, 4242, &BoapFactory::createUdpProtocolHandler);

        sched->setUdp(&udpServer);

        boost::asio::io_service sig_io_service;
        boost::asio::signal_set signals(sig_io_service);
        signals.add(SIGINT);
        signals.async_wait(std::bind(&Net::TcpServer::stop, &tcpServer));
        signals.async_wait(std::bind(&Net::UdpServer::stop, &udpServer));
        signals.async_wait(std::bind(&Server::stop, server.get()));
        signals.async_wait(std::bind(&SqlHandler::stop, &sql));

        tcpThread = std::thread(start_tcp, &tcp_io_service);
        udpThread = std::thread(start_udp, &udp_io_service);
        gameServerThread = std::thread(start_gameserver, server.get());

        sig_io_service.run();
        tcpThread.join();
        udpThread.join();
        gameServerThread.join();
        sqlThread.join();
        delete sched;
    }
    catch (std::exception const & e)
    {
        ERROR("Exception: " << e.what());
        tcpThread.join();
        udpThread.join();
        gameServerThread.join();
        sqlThread.join();
        return -1;
    }
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
