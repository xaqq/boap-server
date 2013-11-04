/* 
 * File:   Scheduler.cpp
 * Author: xaqq
 * 
 * Created on November 4, 2013, 2:56 PM
 */

#include "Scheduler.hpp"

Scheduler *Scheduler::instance_ = nullptr;

Scheduler::Scheduler() { }

void Scheduler::setUdp(Net::UdpServer* udp_)
{
  this->udp_ = udp_;
}

void Scheduler::setTcp(Net::TcpServer* tcp_)
{
  this->tcp_ = tcp_;
}

void Scheduler::setServer(Server* srv)
{
  this->server_ = srv;
}

Scheduler::~Scheduler() { }

Scheduler *Scheduler::instance()
{
  if (instance_ == nullptr)
    return instance_ = new Scheduler();
  return instance_;
}

