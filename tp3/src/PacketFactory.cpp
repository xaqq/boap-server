/* 
 * File:   PacketFactory.cpp
 * Author: xaqq
 * 
 * Created on November 5, 2013, 10:42 AM
 */

#include "PacketFactory.hpp"
#include "ByteArray.hpp"
#include "APacket.hpp"
#include "HelloPacket.hpp"
#include "Log.hpp"
PacketFactory::PacketFactory() { }

PacketFactory::~PacketFactory() { }

std::shared_ptr<APacket> PacketFactory::buildPacket(std::shared_ptr<AClient> source,
                                                    std::size_t opcode, ByteArray && data)
{

  std::shared_ptr<APacket> p;
  switch (opcode)
    {
    case APacket::CMSG_HELLO:
      p = std::make_shared<HelloPacket>(source);
      p->unserialize(std::move(data));
      break;
    default:
      WARN("Opcode not found when building packet");
      break;
    }
  return p;  
}