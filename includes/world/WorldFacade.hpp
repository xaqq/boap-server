/* 
 * File:   WorldFacade.hpp
 * Author: xaqq
 *
 * Created on November 20, 2013, 12:50 AM
 */

#ifndef WORLDFACADE_HPP
#define	WORLDFACADE_HPP

#include <memory>

#include "GameEntity.hpp"
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
   * Spawn an entity into the world.
   * This api call will take care of instancing the object.
   * @param entityId
   * @param pos position in the world
   * @param rot rotation in the world
   * @return A pointer to the new entity, or nullptr
   */
  virtual std::shared_ptr<GameEntity> spawn(int entityId, btVector3 pos, btVector3 rot) = 0;

  /**
   * Remove a btCollisionObject from the collision world.
   * @param e
   */
  virtual void removeFromCollisionWorld(btCollisionObject *o) = 0;

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

  /**
   * Returns the list of entities in the world
   */
  virtual std::list<std::shared_ptr<GameEntity >> entities() = 0;

  /**
   * Return the current navMeshQuery to use
   * @return 
   */
  virtual class dtNavMeshQuery *navMeshQuery() = 0;
};

#endif	/* WORLDFACADE_HPP */

