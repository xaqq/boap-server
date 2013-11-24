/* 
 * File:   AMainThreadGameObserver.cpp
 * Author: xaqq
 * 
 * Created on November 23, 2013, 9:25 PM
 */

#include "observers/AMainThreadGameObserver.hpp"
#include "Scheduler.hpp"
#include "Client.hpp"

AMainThreadGameObserver::AMainThreadGameObserver() { }

AMainThreadGameObserver::~AMainThreadGameObserver() { }

void AMainThreadGameObserver::gameStopped(std::shared_ptr<Game> game, SMSGGameStatus::Status st)
{
  Scheduler::instance()->runInServerThread(std::bind(&AMainThreadGameObserver::onGameStopped, this, game, st));
}

void AMainThreadGameObserver::clientJoined(std::shared_ptr<Game> game, std::shared_ptr<Client>c)
{
  Scheduler::instance()->runInServerThread(std::bind(&AMainThreadGameObserver::onClientJoined, this, game, c));
}