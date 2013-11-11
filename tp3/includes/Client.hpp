/* 
 * File:   Client.hpp
 * Author: xaqq
 *
 * Created on November 3, 2013, 5:40 PM
 */

#ifndef CLIENT_HPP
#define	CLIENT_HPP

#include <memory>
#include "AClient.hpp"

class Client : public AClient
{
public:
  Client();
  Client(const Client& orig) = delete;
  virtual ~Client();
  
};

#endif	/* CLIENT_HPP */

