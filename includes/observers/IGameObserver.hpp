/* 
 * File:   IGameObserver.hpp
 * Author: xaqq
 *
 * Created on November 23, 2013, 9:08 PM
 */

#ifndef IGAMEOBSERVER_HPP
#define	IGAMEOBSERVER_HPP

#include <memory>
#include "ProtobufDef.hpp"
class Game;

/**
 * Interface to observe a game.
 * 
 * Note that this use a Non Virtual Interface pattern because it helps with handling
 * thread problem.
 * 
 * The gameStopped() method is called by the game which stopped. That means that
 * this code runs in the game thread. If you want to handle the event in an other thread all you
 * have to do is override gameStopped() and schedule a call to onGameStopped();
 */
class IGameObserver : public std::enable_shared_from_this<IGameObserver>
{
public:

  IGameObserver() { }

  virtual ~IGameObserver() { }

  /**
   * When a game stopped, it calls this method of the observer;
   * The observer will then ensure to call onGameStopped();
   * @param game
   * @param st
   */
  virtual void gameStopped(std::shared_ptr<Game> game, SMSGGameStatus::Status st)
  {
    onGameStopped(game, st);
  }

  virtual void clientJoined(std::shared_ptr<Game> game, std::shared_ptr<class Client>c)
  {
    onClientJoined(game, c);
  }

private:
  /**
   * A game has stop - do what you want;   * 
   * 
   * @param game The game which stopped;
   * @param st The reason why
   */
  virtual void onGameStopped(std::shared_ptr<Game> game, SMSGGameStatus::Status st) = 0;


  /**
   * A client has joined a game!
   * @param game
   * @param c
   */
  virtual void onClientJoined(std::shared_ptr<Game> game, std::shared_ptr<Client> c) = 0;
};

#endif	/* IGAMEOBSERVER_HPP */

