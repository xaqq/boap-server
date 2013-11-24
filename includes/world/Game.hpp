/* 
 * File:   Game.hpp
 * Author: xaqq
 *
 * Created on November 21, 2013, 11:32 PM
 */

#ifndef GAME_HPP
#define	GAME_HPP

#include "observers/Observable.hpp"
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include "Uuid.hpp"
#include "GameEntity.hpp"
#include "SafeQueue.hpp"
#include "APacket.hpp"
#include "observers/IGameObserver.hpp"
class Server;

class Client;
class Game : public Observable<IGameObserver>, public std::enable_shared_from_this<Game>
{
private:
  
  std::map<std::shared_ptr<Client>, std::shared_ptr<GameEntity>> playersToEntities_;

  /**
   * Name of the game
   */
  std::string name_;
  /**
   * Name of the scene (world name)
   */
  std::string sceneName_;
  std::atomic_bool isRunning_;
  Uuid uuid_;
  mutable std::mutex mutex_;

  /**
   * Entities -- this would be the entity matching each real player and entity representing AI;
   */
  std::list<std::shared_ptr<GameEntity >> entities_;

  /**
   * Initialize the game; This is called once the game is in its own thread.
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
  Game(const std::string &scene);
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
   * Call by handler when a client request a join.
   * @return 
   */
  bool joinGame(std::shared_ptr<Client> client);

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
  const std::string &sceneName() const
  {
    std::lock_guard<std::mutex> guard(mutex_);
    return sceneName_;
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

