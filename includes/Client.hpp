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
#include "ProtobufDef.hpp"
#include "AClient.hpp"
#include "observers/AMainThreadGameObserver.hpp"

class Game;
class Client : public AClient
{
public:
  Client();
  Client(const Client& orig) = delete;
  virtual ~Client();
  
  /**
   * This is a helper class for a client to observer a main. Allow for a easy workaround around
   * the multiple inheritance of shared_from_this();
   * 
   */
  class GameObserver : public AMainThreadGameObserver
  {
  private:
    /**
     * This means that someone joined the game this client is in
     */
    void onClientJoined(std::shared_ptr<Game>, std::shared_ptr<Client> c);
    void onGameStopped(std::shared_ptr<Game>, SMSGGameStatus::Status st);
  };
  
  friend class GameObserver;
private:
  /**
   * Observer instance
   */
  std::shared_ptr<GameObserver> observer_;
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

