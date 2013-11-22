/* 
 * File:   SMSGUdpCode.hpp
 * Author: xaqq
 *
 * Created on November 20, 2013, 3:42 AM
 */

#ifndef SMSGUDPCODE_HPP
#define	SMSGUDPCODE_HPP

#include <memory>
#include <string>
#include "APacket.hpp"

/**
 * Server message sending UDP auth code
 */
class SMSGUdpCode : public APacket
{
public:
  SMSGUdpCode(std::shared_ptr<AClient> source);
  SMSGUdpCode(const SMSGUdpCode&) = delete;
  virtual ~SMSGUdpCode();

  /**
   * This function MUST be implemented in all APacket's subclasses; This is
   * required because this allows for double dispatch to happen.
   * 
   * 
   * @param handler
   */
  virtual bool acceptHandler(APacketHandler *handler);

  virtual void unserialize(ByteArray data);
  virtual ByteArray serialize() const;

  std::string authCode_;
};

#endif	/* SMSGUDPCODE_HPP */

