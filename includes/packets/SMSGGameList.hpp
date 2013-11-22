#pragma once

#include <tuple>
#include <string>  
#include <map>
#include "APacket.hpp"
#include "ByteArray.hpp"
#include "ProtobufDef.hpp"

class APacketHandler;

/**
 *  Packet sent by client when they want to create a new game
 */
class SMSGGameList : public APacket
{
public:
  SMSGGameList(std::shared_ptr<AClient> source);
  SMSGGameList(const SMSGGameList& orig);
  virtual ~SMSGGameList();

  virtual void unserialize(ByteArray data) override;

  virtual ByteArray serialize() const;

  SMSGGameListData data_;
};