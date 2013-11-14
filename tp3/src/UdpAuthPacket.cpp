/* 
 * File:   UdpAuthPacket.cpp
 * Author: xaqq
 * 
 * Created on November 11, 2013, 3:35 PM
 */

#include "UdpAuthPacket.hpp"

#include <assert.h>
#include <string>
#include "HelloPacket.hpp"
#include "APacketHandler.hpp"

UdpAuthPacket::UdpAuthPacket(std::shared_ptr<AClient> source) : APacket(source) { }

UdpAuthPacket::~UdpAuthPacket() { }

bool UdpAuthPacket::acceptHandler(APacketHandler* handler)
{
  bool ret = true;
  ret &= APacket::acceptHandler(handler);
  ret &= handler->handle(this);

  return true;
}

void UdpAuthPacket::unserialize(ByteArray data)
{
  authCode_.append(data.begin(), data.end());
}

ByteArray UdpAuthPacket::serialize() const
{
  return ByteArray(0);
}

const std::string &UdpAuthPacket::authCode() const
{
  return authCode_;
}

std::shared_ptr<Net::AUdpProtocolHandler> UdpAuthPacket::handler()
{
  return handler_;
}

void UdpAuthPacket::handler(std::shared_ptr<Net::AUdpProtocolHandler> h)
{
  handler_ = h;
}