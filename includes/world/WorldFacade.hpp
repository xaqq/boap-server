/* 
 * File:   WorldFacade.hpp
 * Author: xaqq
 *
 * Created on November 20, 2013, 12:50 AM
 */

#ifndef WORLDFACADE_HPP
#define	WORLDFACADE_HPP

#include <memory>
class GameEntity;

/**
 * This is an interface implemented by the WorldObject. It is passed to the gameEntity object
 * so that have a nice interface to use.
 */
class WorldFacade
{
public:
  /**
   * Spawn an entity into the world.
   * This api call will take care of instancing the object.
   * @param entityId
   * @return A pointer to the new entity, or nullptr
   */
  virtual std::shared_ptr<GameEntity> spawn(int entityId) = 0;

  /**
   * Register an observer to be notified by world event.
   * 
   * Observers are currently not thread-safe
   */
  virtual void registerOberserver(class IWorldObserver *) = 0;

  /**
   * Remove the observer so that it is no longer notified of event.
   * @param the observer
   */
  virtual void unregisterObserver(IWorldObserver *) = 0;
};

#endif	/* WORLDFACADE_HPP */

