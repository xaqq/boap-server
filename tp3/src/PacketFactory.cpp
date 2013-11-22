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
#include "CMSGAuthPacket.hpp"
#include "CMSGCreateGame.hpp"

PacketFactory::PacketFactory() { }

PacketFactory::~PacketFactory() { }

std::shared_ptr<APacket> PacketFactory::buildPacket(std::shared_ptr<AClient> source,
                                                    std::size_t opcode, ByteArray data)
{
  WARN("LMAMA BUILD PACKET" << opcode << ")");
  std::shared_ptr<APacket> p;
  switch (opcode)
    {
    case APacket::CMSG_HELLO:
      p = std::make_shared<HelloPacket > (source);
      p->unserialize(std::move(data));
      break;

    case APacket::CMSG_AUTH:
      p = std::make_shared<CMSGAuthPacket > (source);
      p->unserialize(std::move(data));
      break;

    case APacket::CMSG_CREATE_GAME:
      p = std::make_shared<CMSGCreateGame > (source);
      p->unserialize(std::move(data));
      break;

    default:
      WARN("Opcode not found when building packet (" << opcode << ")");
      return nullptr;
    }
  return p;
}