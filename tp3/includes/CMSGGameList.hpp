#pragma once
#include "APacket.hpp"

class CMSGGameList : public APacket
{
public:

  CMSGGameList  (std::shared_ptr<class AClient> src) : APacket(src) { }

  ~CMSGGameList  () { }
  CMSGGameList  (const CMSGGameList &);
  void unserialize(ByteArray data);
  ByteArray serialize();
private:
};
