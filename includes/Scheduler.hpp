/* 
 * File:   Scheduler.hpp
 * Author: xaqq
 *
 * Created on November 4, 2013, 2:56 PM
 */

#ifndef SCHEDULER_HPP
#define	SCHEDULER_HPP

#include <functional>

#include "net/TcpServer.hpp"
#include "net/UdpServer.hpp"
#include "Server.hpp"

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

public:
  virtual ~Scheduler();

  static Scheduler *instance();

  void runInTcpThread(std::function<void()> f)
  {
    tcp_->ioService().post(f);
  }
  
  void runInUdpThread(std::function<void()> f)
  {
    udp_->ioService().post(f);
  }
  
  void runInServerThread(std::function<void()> f)
  {
    server_->post(f);
  }

  void setUdp(Net::UdpServer* udp);
  void setTcp(Net::TcpServer* tcp);
  void setServer(Server* srv);

};

#endif	/* SCHEDULER_HPP */

