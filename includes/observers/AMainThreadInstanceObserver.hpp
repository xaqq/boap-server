/* 
 * File:   AMainThreadInstanceObserver.hpp
 * Author: xaqq
 *
 * Created on November 23, 2013, 9:25 PM
 */

#ifndef AMAINTHREADINSTANCEOBSERVER_HPP
#define	AMAINTHREADINSTANCEOBSERVER_HPP

#include "observers/IAreaInstanceObserver.hpp"

/**
 * Abstract GameObserver that schedule event handling to happen in main thread.
 * 
 * This is useful for clients and server that observe games.
 */
class AMainThreadInstanceObserver : public IAreaInstanceObserver
{
public:
  AMainThreadInstanceObserver();
  AMainThreadInstanceObserver(const AMainThreadInstanceObserver& orig) = delete;
  virtual ~AMainThreadInstanceObserver();

  /**
   * Override to dispatch the call to the main thread.
   */
  virtual void instanceStopped(std::shared_ptr<AreaInstance> game, SMSGGameStatus::Status st) override;

  virtual void clientJoined(std::shared_ptr<AreaInstance> game, std::shared_ptr<class Client>c) override;

private:
  virtual void onInstanceStopped(std::shared_ptr<AreaInstance> game, SMSGGameStatus::Status st) override = 0;

  virtual void onClientJoined(std::shared_ptr<AreaInstance> game, std::shared_ptr<class Client>c) override = 0;
};

#endif	/* AMAINTHREADINSTANCEOBSERVER_HPP */

