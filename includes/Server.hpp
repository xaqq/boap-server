/* 
 * File:   Server.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 6:24 PM
 */

#ifndef SERVER_HPP
#define	SERVER_HPP

#include <atomic>

class Server
{
public:
  Server();
  Server(const Server& orig) = delete;
  virtual ~Server();
  
  /**
   * Call to shutdown the server;
   */
  void stop();
  
  /**
   * Server main loop;
   */
  void run();
private:
  std::atomic_bool isRunning_;

};

#endif	/* SERVER_HPP */

