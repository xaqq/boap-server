/* 
 * File:   APacket.hpp
 * Author: xaqq
 *
 * Created on November 4, 2013, 7:10 PM
 */
#pragma once

#include <memory>
#include "ByteArray.hpp"
#include "handlers/APacketHandler.hpp"
class AClient;
class APacketHandler;

class APacket
{
public:
  APacket(std::shared_ptr<AClient> source);
  APacket(const APacket& orig);
  virtual ~APacket();

  /**
   * Returns a pointer to the source of the packet.
   * 
   * Wether source is nullptr or not depends if the packet handler responsible for this
   * packet creation had a client registered of not.
   * 
   * Also, when the APacket objet is a output packet, source may be left to nullptr;
   * @return Pointer to the source. May be nullptr;
   */
  std::shared_ptr<AClient> source();

  /**
   * This function MUST be implemented in all APacket's subclasses; This is
   * required because this allows for double dispatch to happen.
   * 
   * 
   * @param handler
   */
  virtual bool acceptHandler(APacketHandler *handler);

  virtual void unserialize(ByteArray data) = 0;
  virtual ByteArray serialize() const = 0;

  enum
  {
    CMSG_HELLO = 0x0001,
    CMSG_AUTH = 0x0010,
    CMSG_CREATE_GAME = 0x0011,
    CMSG_GAME_LIST = 0x0012,
    CMSG_JOIN_GAME = 0x0013,
    SMSG_MOTD = 0x1001,
    SMSG_UDP_CODE = 0x1002,
    SMSG_AUTH = 0x1010,
    SMSG_CREATE_GAME = 0x1011,
    SMSG_GAME_LIST = 0x1012,
    SMSG_JOIN_GAME = 0x1013
  };

protected:
  std::shared_ptr<AClient> source_;

};
