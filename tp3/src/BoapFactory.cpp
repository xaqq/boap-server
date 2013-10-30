#include "BoapFactory.hpp"
#include "net/DefaultTcpProtocolHandler.hpp"
#include "net/TcpSession.hpp"
#include "TcpProtocolHandler.hpp"

std::shared_ptr<Net::ITcpProtocolHandler> BoapFactory::createTcpProtocolHandler(Net::TcpSession &session)
{
  return std::shared_ptr<Net::ITcpProtocolHandler> (new Net::TcpProtocolHandler(session));
}
