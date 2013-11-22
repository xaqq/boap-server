/* 
 * File:   Game.hpp
 * Author: xaqq
 *
 * Created on November 21, 2013, 11:32 PM
 */

#ifndef GAME_HPP
#define	GAME_HPP

#include <thread>
#include <mutex>
#include <atomic>
#include "Uuid.hpp"
#include "GameEntity.hpp"
#include "SafeQueue.hpp"
#include "APacket.hpp"
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
  mutable std::mutex mutex_;

  /**
   * Entities -- this would be the entity matching each real player and entity representing AI;
   */
  std::list<std::shared_ptr<GameEntity >> entities_;

  /**
   * Initialise the game; This is called once the game is in its own thread.
   */
  bool init();

  /**
   * The world !
   */
  class World *world_;

  /**
   * Handle packets
   */
  void handle_packets();

  typedef SafeQueue<std::shared_ptr<APacket >> PacketList;
  typedef std::list<std::shared_ptr<APacketHandler >> PacketHandlerList;

  PacketHandlerList packetHandlers_;
  PacketList packets_;

public:

  Game();
  Game(const Game& orig) = delete;
  virtual ~Game();


  const std::string &uuid() const;

  /**
   * Game main loop
   */
  void run();

  /**
   * Thread safe
   * @return 
   */
  const std::string &name() const
  {
    std::lock_guard<std::mutex> guard(mutex_);
    return name_;
  }

  /**
   * Thread safe
   * @param s
   */
  void name(const std::string &s)
  {
    std::lock_guard<std::mutex> guard(mutex_);
    name_ = s;
  }

  /**
   * Thread safe
   * @return 
   */
  int countPlayers() const;

  /**
   * Instruct the game to shutdown
   */
  void stop();

  /**
   * Use to push a packet that will be handled later; 
   * This is thread safe;
   */
  void pushPacket(std::shared_ptr<APacket> p)
  {
    packets_.push(p);
  }



};

#endif	/* GAME_HPP */

