#include <string>
#include "packets/CMSGUdpAuth.hpp"

CMSGUdpAuth::CMSGUdpAuth(std::shared_ptr<AClient> source) : APacket(source) { }

CMSGUdpAuth::~CMSGUdpAuth() { }

bool CMSGUdpAuth::acceptHandler(APacketHandler* handler)
{
  bool ret = true;
  ret &= APacket::acceptHandler(handler);
  ret &= handler->handle(this);

  return true;
}

void CMSGUdpAuth::unserialize(ByteArray data)
{
  authCode_.append(data.begin(), data.end());
}

ByteArray CMSGUdpAuth::serialize() const
{
  return ByteArray(0);
}

const std::string &CMSGUdpAuth::authCode() const
{
  return authCode_;
}

std::shared_ptr<Net::AUdpProtocolHandler> CMSGUdpAuth::handler()
{
  return handler_;
}

void CMSGUdpAuth::handler(std::shared_ptr<Net::AUdpProtocolHandler> h)
{
  handler_ = h;
}