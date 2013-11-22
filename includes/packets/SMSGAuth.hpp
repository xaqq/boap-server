#pragma once
#include <string>
#include "APacket.hpp"
#include "AuthTask.hpp"
#include "ProtobufDef.hpp"

/**
 * Packet sent by server after a game creation request
 */
class SMSGAuth : public APacket
{
public:
  SMSGAuth(std::shared_ptr<AClient> source);
  SMSGAuth(std::shared_ptr<AClient> source, SMSGAuthData::AuthResult res);
  SMSGAuth(const SMSGAuth& orig);
  virtual ~SMSGAuth();


  virtual void unserialize(ByteArray data);

  /**
   * Binary representation:
   *   [value from AuthTask::AuthResult] <-- ascii char
   *   [error message]
   * @return 
   */
  virtual ByteArray serialize() const;
  
  std::string getMsg() const;
  SMSGAuthData data_;
  
  
};