/* 
 * File:   SMSGAuth.cpp
 * Author: xaqq
 * 
 * Created on November 22, 2013, 12:24 AM
 */

#include <string>
#include "packets/SMSGAuth.hpp"
#include "Log.hpp"
#include "AClient.hpp"

SMSGAuth::SMSGAuth(std::shared_ptr<AClient> source) : APacket(source) { }

SMSGAuth::SMSGAuth(std::shared_ptr<AClient> source, SMSGAuthData::AuthResult res) : APacket(source)
{
  data_.set_result(res);
}

SMSGAuth::SMSGAuth(const SMSGAuth &o) : APacket(o.source_)
{
  data_ = o.data_;
}

SMSGAuth::~SMSGAuth() { }

void SMSGAuth::unserialize(ByteArray) { }

std::string SMSGAuth::getMsg() const
{
  std::string msg;

  switch (data_.result())
    {
    case SMSGAuthData::OK:
      msg = "Auth is successfull";
      break;
    case SMSGAuthData::INTERNAL_ERROR:
      msg = "An Internal error occurred, preventing the login";
      break;
    case SMSGAuthData::WRONG_PASSWORD:
      msg = "Password is invalid";
      break;
    case SMSGAuthData::UNKNOWN_USER:
      msg = "Unknown user";
      break;
    }
  return msg;
}

ByteArray SMSGAuth::serialize() const
{
  ByteArray b;
  std::string msg;
  SMSGAuthData out = data_;
  
  out.set_message(getMsg());
  if (!out.SerializeToString(&msg))
    {
      WARN("Cannot serialize: " << out.DebugString());
      return ByteArray(0);
    }
  
  b << APacket::SMSG_AUTH;
  b << msg.length();
  b.insert(b.end(), msg.begin(), msg.end());
  return b;
}