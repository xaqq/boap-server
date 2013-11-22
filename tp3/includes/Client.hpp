/* 
 * File:   Client.hpp
 * Author: xaqq
 *
 * Created on November 3, 2013, 5:40 PM
 */

#ifndef CLIENT_HPP
#define	CLIENT_HPP

#include <string>
#include <memory>
#include "AClient.hpp"

class Client : public AClient
{
public:
  Client();
  Client(const Client& orig) = delete;
  virtual ~Client();

private:
  bool authenticated_;
  std::string username_;
  std::string udpAuthCode_;

public:

  void udpAuthCode(std::string code);
  const std::string &udpAuthCode() const;

  const std::string &username() const
  {
    return username_;
  }

  void username(const std::string &username)
  {
    username_ = username;
  }

  bool authenticated() const
  {
    return authenticated_;
  }

  void authenticated(bool v)
  {
    authenticated_ = v;
  }

};

#endif	/* CLIENT_HPP */

