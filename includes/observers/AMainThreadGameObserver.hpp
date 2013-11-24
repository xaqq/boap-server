/* 
 * File:   AMainThreadGameObserver.hpp
 * Author: xaqq
 *
 * Created on November 23, 2013, 9:25 PM
 */

#ifndef AMAINTHREADGAMEOBSERVER_HPP
#define	AMAINTHREADGAMEOBSERVER_HPP

#include "observers/IGameObserver.hpp"

/**
 * Abstract GameObserver that schedule event handling to happen in main thread.
 * 
 * This is useful for clients and server that observe games.
 */
class AMainThreadGameObserver : public IGameObserver
{
public:
  AMainThreadGameObserver();
  AMainThreadGameObserver(const AMainThreadGameObserver& orig) = delete;
  virtual ~AMainThreadGameObserver();

  /**
   * Override to dispatch the call to the main thread.
   */
  virtual void gameStopped(std::shared_ptr<Game> game, SMSGGameStatus::Status st) override;

  virtual void clientJoined(std::shared_ptr<Game> game, std::shared_ptr<class Client>c) override;

private:
  virtual void onGameStopped(std::shared_ptr<Game> game, SMSGGameStatus::Status st) override = 0;

  virtual void onClientJoined(std::shared_ptr<Game> game, std::shared_ptr<class Client>c) override = 0;
};

#endif	/* AMAINTHREADGAMEOBSERVER_HPP */

