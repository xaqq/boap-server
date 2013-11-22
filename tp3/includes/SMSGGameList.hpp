#pragma once

#include <tuple>
#include <string>  
#include <map>
#include "APacket.hpp"
#include "ByteArray.hpp"

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

  /**
   * Binary layout: 
   *  unsigned short <-- nbGame
   * uuid \0 gameName \0 unsigned short <-- nbPlayerInGame
   */
  virtual ByteArray serialize() const;

  std::map < std::string /*uuid*/, std::pair<std::string /*name*/, std::uint16_t >> games_;

private:
  ByteArray buildContent() const;
};