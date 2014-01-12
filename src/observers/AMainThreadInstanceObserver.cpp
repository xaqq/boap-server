/* 
 * File:   AMainThreadInstanceObserver.cpp
 * Author: xaqq
 * 
 * Created on November 23, 2013, 9:25 PM
 */

#include "observers/AMainThreadInstanceObserver.hpp"
#include "Scheduler.hpp"
#include "Client.hpp"

AMainThreadInstanceObserver::AMainThreadInstanceObserver() { }

AMainThreadInstanceObserver::~AMainThreadInstanceObserver() { }

void AMainThreadInstanceObserver::instanceStopped(std::shared_ptr<AreaInstance> game, SMSGGameStatus::Status st)
{
  Scheduler::instance()->runInServerThread(std::bind(&AMainThreadInstanceObserver::onInstanceStopped, this, game, st));
}

void AMainThreadInstanceObserver::clientJoined(std::shared_ptr<AreaInstance> game, std::shared_ptr<Client>c)
{
  Scheduler::instance()->runInServerThread(std::bind(&AMainThreadInstanceObserver::onClientJoined, this, game, c));
}