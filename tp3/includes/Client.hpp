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

  void udpAuthCode(std::string code);
  const std::string &udpAuthCode() const;

private:
  std::string udpAuthCode_;
};

#endif	/* CLIENT_HPP */

