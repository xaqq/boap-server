/* 
 * File:   ATcpProtocolHandler.cpp
 * Author: xaqq
 * 
 * Created on October 30, 2013, 1:42 AM
 */

#include "APacket.hpp"
#include "net/ATcpProtocolHandler.hpp"
#include "Scheduler.hpp"
using namespace Net;

ATcpProtocolHandler::ATcpProtocolHandler(TcpSession &session) : ITcpProtocolHandler(session),
session_(session) { }

ATcpProtocolHandler::~ATcpProtocolHandler() { }

TcpSession & ATcpProtocolHandler::session()
{
  return session_;
}

const TcpSession & ATcpProtocolHandler::session() const
{
  return session_;
}

void ATcpProtocolHandler::pushPacket(std::shared_ptr<APacket> p)
{
  session().post(p->serialize());
}

void ATcpProtocolHandler::disconnect()
{
  Scheduler::instance()->runInTcpThread(std::bind(&TcpSession::quit, &session()));
  //session().quit();
}