/* 
 * File:   SMSGCreateGame.hpp
 * Author: xaqq
 *
 * Created on November 22, 2013, 12:24 AM
 */

#ifndef SMSGCREATEGAME_HPP
#define	SMSGCREATEGAME_HPP

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

  /**
   * Binary representation:
   *   [1|0] <-- ascii char
   *   [gameUuid|errMsg]    <-- string
   * @return 
   */
  virtual ByteArray serialize() const;
  
  bool success_;
  
  /**
   * Only set if success is false
   */
  std::string errMsg_;
  
  /**
   * The string representation of the new game's uuid.
   */
  std::string gameUuid_;

  private:
    int  binaryLength() const;;
  
};

#endif	/* SMSGCREATEGAME_HPP */

