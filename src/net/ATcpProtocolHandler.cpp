/* 
 * File:   ATcpProtocolHandler.cpp
 * Author: xaqq
 * 
 * Created on October 30, 2013, 1:42 AM
 */

#include "APacket.hpp"
#include "net/ATcpProtocolHandler.hpp"
#include "Scheduler.hpp"
#include "Log.hpp"
#include "net/TcpSession.hpp"
using namespace Net;

ATcpProtocolHandler::ATcpProtocolHandler() { }

ATcpProtocolHandler::~ATcpProtocolHandler()
{
  DEBUG("ProtocolHandler destroyed");
}

bool ATcpProtocolHandler::pushPacket(std::shared_ptr<APacket> p)
{
  auto session = session_.lock();

  if (session)
    return session->post(std::move(p->serialize()));
  return false;
}

bool ATcpProtocolHandler::write(const std::string& s)
{
  auto session = session_.lock();
  ByteArray data;
  
  data.resize(s.length());
  std::memcpy(&data[0], s.c_str(), s.length());
  if (session)
    return session->post(std::move(data));
  return false;
}

void ATcpProtocolHandler::disconnect()
{
  auto session = session_.lock();

  if (session)
    Scheduler::instance()->runInTcpThread(std::bind(&TcpSession::stop, session, true)); //graceful
  else
    {
      WARN("Calling disconnect on protocol handler whose session is off");
    }
}

void ATcpProtocolHandler::disconnected()
{
  DEBUG("ProtocolHandler disconnected...");
}

bool ATcpProtocolHandler::request(std::size_t size)
{
  auto session = session_.lock();

  if (session)
    {
      session->request(size);
      return true;
    }
  WARN("request() called but the session has been destroyed already");
  return false;
}

void ATcpProtocolHandler::setSession(std::shared_ptr<TcpSession> session)
{
  session_ = session;
}