#pragma once
#include "APacket.hpp"

class CMSGGameList : public APacket
{
public:

  CMSGGameList(std::shared_ptr<AClient>);

  virtual ~CMSGGameList() { }
  CMSGGameList(const CMSGGameList &);

  bool acceptHandler(APacketHandler* handler);

  void unserialize(ByteArray data);
  ByteArray serialize()const;
private:
};
