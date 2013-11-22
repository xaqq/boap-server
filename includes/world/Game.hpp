/* 
 * File:   Game.hpp
 * Author: xaqq
 *
 * Created on November 21, 2013, 11:32 PM
 */

#ifndef GAME_HPP
#define	GAME_HPP

#include <atomic>
#include "Uuid.hpp"
class Server;

class Game
{
private:

  /**
   * Name of the game
   */
  std::string name_;
  std::atomic_bool isRunning_;
  Uuid uuid_;

public:
  Game();
  Game(const Game& orig) = delete;
  virtual ~Game();


  const std::string &uuid() const;

  /**
   * Game main loop
   */
  void run();

  const std::string &name() const
  {
    return name_;
  }

  void name(const std::string &s)
  {
    name_ = s;
  }
  
  /**
   * Instruct the game to shutdown
   */
  void stop();

};

#endif	/* GAME_HPP */

