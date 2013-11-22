/* 
 * File:   SMSGCreateGame.hpp
 * Author: xaqq
 *
 * Created on November 22, 2013, 12:24 AM
 */

#ifndef SMSGCREATEGAME_HPP
#define	SMSGCREATEGAME_HPP

#include "ProtobufDef.hpp"
#include "APacket.hpp"

/**
 * Packet sent by server after a game creation request
 */
class SMSGCreateGame : public APacket
{
public:
  SMSGCreateGame(std::shared_ptr<AClient> source);
  SMSGCreateGame(const SMSGCreateGame& orig);
  virtual ~SMSGCreateGame();


  virtual void unserialize(ByteArray data);
  virtual ByteArray serialize() const;

  SMSGCreateGameData data_;
  
};

#endif	/* SMSGCREATEGAME_HPP */

