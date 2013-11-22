/* 
 * File:   PacketFactory.cpp
 * Author: xaqq
 * 
 * Created on November 5, 2013, 10:42 AM
 */

#include "packets/PacketFactory.hpp"
#include "ByteArray.hpp"
#include "APacket.hpp"

#include "packets/HelloPacket.hpp"
#include "Log.hpp"
#include "packets/CMSGAuthPacket.hpp"
#include "packets/CMSGCreateGame.hpp"
#include "packets/CMSGGameList.hpp"

PacketFactory::PacketFactory() { }

PacketFactory::~PacketFactory() { }

std::shared_ptr<APacket> PacketFactory::buildPacket(std::shared_ptr<AClient> source,
                                                    std::size_t opcode, ByteArray data)
{
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

    case APacket::CMSG_GAME_LIST:
      p = std::shared_ptr<CMSGGameList > (new CMSGGameList(source));
      p->unserialize(std::move(data));
      break;

    default:
      INFO("Opcode not found when building packet (" << opcode << ")");
      return nullptr;
    }
  return p;
}