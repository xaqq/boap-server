/* 
 * File:   SMSGAuth.cpp
 * Author: xaqq
 * 
 * Created on November 22, 2013, 12:24 AM
 */

#include <string>
#include "SMSGAuth.hpp"
#include "AClient.hpp"

SMSGAuth::SMSGAuth(std::shared_ptr<AClient> source) : APacket(source) { }

SMSGAuth::SMSGAuth(std::shared_ptr<AClient> source, AuthTask::AuthResult res) : APacket(source),
result_(res) { }

SMSGAuth::SMSGAuth(const SMSGAuth &o) : APacket(o.source_)
{
  result_ = o.result_;
}

SMSGAuth::~SMSGAuth() { }

void SMSGAuth::unserialize(ByteArray) { }

ByteArray SMSGAuth::buildContent(int &size) const
{
  ByteArray res;
  std::string msg;

  switch (result_)
    {
    case AuthTask::AuthResult::OK:
      msg = "Auth is successfull";
      break;
    case AuthTask::AuthResult::INTERNAL_ERROR:
      msg = "An Internal error occurred, preventing the login";
      break;
    case AuthTask::AuthResult::WRONG_PASSWORD:
      msg = "Password is invalid";
      break;
    case AuthTask::AuthResult::UNKNOWN_USER:
      msg = "Unknown user";
      break;
    }
  size = sizeof (AuthTask::AuthResult) + msg.length();
  assert(sizeof (unsigned char) == sizeof (AuthTask::AuthResult));
  res << static_cast<unsigned char> (result_);
  res << msg;
  return res;
}

ByteArray SMSGAuth::serialize() const
{
  ByteArray b;
  ByteArray content;
  int size = 0;
  content = buildContent(size);

  b << APacket::SMSG_AUTH;
  b << size;
  b.insert(b.end(), content.begin(), content.end());
  return b;
}