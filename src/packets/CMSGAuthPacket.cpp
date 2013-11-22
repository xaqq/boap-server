/* 
 * File:   HelloPacket.cpp
 * Author: xaqq
 * 
 * Created on November 4, 2013, 8:45 PM
 */
#include "packets/CMSGAuthPacket.hpp"
#include <assert.h>
#include "Log.hpp"
#include "handlers/APacketHandler.hpp"
#include <string>
#include <algorithm>
//#include "protobuf/ProtobufDef.hpp"

CMSGAuthPacket::CMSGAuthPacket(std::shared_ptr<AClient> source) : APacket(source) { }

CMSGAuthPacket::CMSGAuthPacket(const CMSGAuthPacket& orig) : APacket(orig)
{
  username_ = orig.username_;
  password_ = orig.password_;
}

CMSGAuthPacket::~CMSGAuthPacket() { }

bool CMSGAuthPacket::acceptHandler(APacketHandler* handler)
{
  bool ret = true;
  ret &= APacket::acceptHandler(handler);
  ret &= handler->handle(this);
  
  return true;
} 

void CMSGAuthPacket::unserialize(ByteArray data)
{
//  
//  CMSGAuthData data;
//  
//  bool ret = buf.ParseFromArray(&data[0], data.size());
//  
//  if (ret)
//    INFO("COOL " << buf.username());
//  else
//    INFO("PAS COOL");
//  
  
  ByteArray::iterator search = std::find(data.begin(), data.end(), '\0');
  if (search == data.end())
    {
      WARN("INVALID PACKET");
      return;
    }
  std::string str(data.begin(), search);
  username_ = std::move(str);
  ++search;
  if (search == data.end())
    {
      WARN("Invalid packet");
      return;
    }
  std::string str2(search, data.end());
  password_ = std::move(str2);
}

ByteArray CMSGAuthPacket::serialize() const
{
  return ByteArray(0);
}