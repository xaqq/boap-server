/* 
 * File:   Scheduler.hpp
 * Author: xaqq
 *
 * Created on November 4, 2013, 2:56 PM
 */

#ifndef SCHEDULER_HPP
#define	SCHEDULER_HPP

#include <functional>
#include "net/Network.hpp"
#include "sql/SqlHandler.hpp"
#include <future>

class Server;
class ISqlResult;
namespace sql
{
  class Connection;
};

/**
 * Scheduler helper;
 * The main() function is responsible for setting it up.
 */
class Scheduler
{
private:
  Scheduler();
  Scheduler(const Scheduler& orig) = delete;

  static Scheduler *instance_;

  Net::TcpServer *tcp_;
  Net::UdpServer *udp_;
  Server *server_;
  SqlHandler *sql_;

public:
  virtual ~Scheduler();

  static Scheduler *instance();

  void runInTcpThread(std::function<void() > f);
  void runInUdpThread(std::function<void() > f);
  void runInServerThread(std::function<void() > f);
  void runInSqlThread(std::function<void (sql::Connection *) > f);

  
  template <typename Callable>
  void runInHelper(Callable c)
  {
      std::thread t1(c);
      
      t1.detach();
  }
  
  
  SqlFutureResult runFutureInSql(std::function<SqlTaskReturnType (sql::Connection *) > f);

  void setUdp(Net::UdpServer* udp);
  void setTcp(Net::TcpServer* tcp);
  void setServer(Server* srv);
  void setSql(SqlHandler *h);

};

#endif	/* SCHEDULER_HPP */

