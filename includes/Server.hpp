/* 
 * File:   Server.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 6:24 PM
 */

#ifndef SERVER_HPP
#define	SERVER_HPP

#include <atomic>
#include <memory>
#include <list>
#include <thread>
#include <map>
#include "SafeQueue.hpp"
#include "APacket.hpp"
#include "world/World.hpp"
#include "observers/AMainThreadGameObserver.hpp"

class APacket;
class AClient;
class APacketHandler;

class Server : public AMainThreadGameObserver
{
public:

  typedef std::map<std::shared_ptr<AClient>, std::shared_ptr<Game>> ClientGameMap;
  typedef std::map<std::shared_ptr<Game>, std::thread> GameThreadMap;
  typedef std::list<std::shared_ptr<Game >> GameList;
  typedef std::list<std::shared_ptr<AClient >> ClientList;
  typedef SafeQueue<std::shared_ptr<APacket >> PacketList;
  typedef std::list<std::shared_ptr<APacketHandler >> PacketHandlerList;


  Server(const Server& orig) = delete;
  virtual ~Server();

  static Server &instance();

  /**
   * Call to shutdown the server;
   */
  void stop();

  /**
   * Server main loop;
   */
  void run();

  /**
   * Asynchronously add the client to the server's client list.
   * This function is thread safe, because it simply queue the call
   * @param c
   */
  void addClient(std::shared_ptr<AClient> c);

  /**
   * Asynchronously remove the client to the server's client list.
   * This function is thread safe, because it simply queue the call
   * @param c
   */
  void removeClient(std::shared_ptr<AClient> c);


  /**
   * This returns the list of client known by the server. This is intended for use by packet handler
   * @return  list of client
   */
  const ClientList &clients() const;

  /**
   * Use to schedule a call of f() in the server's thread.
   * This method is thread safe.
   * @param f
   */
  void post(std::function<void() > f)
  {
    operationQueue_.push(f);
  }

  /**
   * Use to push a packet that will be handled later; 
   * This is thread safe;
   */
  void pushPacket(std::shared_ptr<APacket> p)
  {
    packets_.push(p);
  }

  /**
   * Add a game and start a thread for it.
   * Making the game name is unique the role of the CreateGameHandler class.
   */
  void addGame(std::shared_ptr<Game> g);

  const GameList &games() const;
  
private:
  Server();
  
  /**
   * Initialize the server, creating required area instance if required, loading up previously saved ones, etc
   * @return 
   */
  bool initialize();

  static Server *instance_;

  std::atomic_bool isRunning_;

  ClientList clients_;
  PacketList packets_;
  PacketHandlerList packetHandlers_;

  /**
   * Invoke queued handler;
   */
  void flush_operations();

  /**
   * Invoke packet handler;
   */
  void handle_packets();

  SafeQueue<std::function<void () >> operationQueue_;


  /**
   * Map between client and game
   */

  ClientGameMap clientGame_;

  GameList gameList_;

  GameThreadMap gameThread_;

  void onGameStopped(std::shared_ptr<Game>, SMSGGameStatus::Status) override;
  void onClientJoined(std::shared_ptr<Game> game, std::shared_ptr<Client> c) override;
};

#endif	/* SERVER_HPP */

