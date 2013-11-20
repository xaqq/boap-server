/* 
 * File:   AdminTcpHandler.cpp
 * Author: xaqq
 * 
 * Created on November 11, 2013, 2:29 PM
 */

#include "AdminTcpHandler.hpp"
#include "Log.hpp"

using namespace Net;
AdminTcpHandler::AdminTcpHandler() { }

AdminTcpHandler::AdminTcpHandler(const AdminTcpHandler&) { }

AdminTcpHandler::~AdminTcpHandler() { }


void AdminTcpHandler::start()
{
  write("Welcome ! This is the AdminTcpHandler. It does nothing except greeting you.\n");
  request(0);
}

void AdminTcpHandler::bytesAvailable(ByteArray bytes)
{
  DEBUG("AdminProtocolhandler has " << bytes.size() << "bytes available.");
  request(0);
}