#pragma once
#include "APacket.hpp"
#include "AuthTask.hpp"

/**
 * Packet sent by server after a game creation request
 */
class SMSGAuth : public APacket
{
public:
  SMSGAuth(std::shared_ptr<AClient> source);
  SMSGAuth(std::shared_ptr<AClient> source, AuthTask::AuthResult res);
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
  
  ByteArray buildContent(int &size) const;
  AuthTask::AuthResult result_;
  
  
};