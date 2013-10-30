/* 
 * File:   ATcpProtocolHandler.cpp
 * Author: xaqq
 * 
 * Created on October 30, 2013, 1:42 AM
 */

#include "net/ATcpProtocolHandler.hpp"
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