#pragma once


class CMSGAuthPacket;

class AuthPacketHandler : public APacketHandler
{
public:
  AuthPacketHandler();
  AuthPacketHandler(const AuthPacketHandler& orig) = delete;
  virtual ~AuthPacketHandler();
  
  virtual bool handle(CMSGAuthPacket *p);
  
private:


};