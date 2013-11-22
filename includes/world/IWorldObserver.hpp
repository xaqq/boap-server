/* 
 * File:   IWorldObserver.hpp
 * Author: xaqq
 *
 * Created on November 20, 2013, 12:41 AM
 */

#ifndef IWORLDOBSERVER_HPP
#define	IWORLDOBSERVER_HPP

#include <memory>

class dtNavMeshQuery;
/**
 * This is an interface to observe the world object. When changes occure the registered observer
 * will be notified;
 * 
 * The PathFindHelper will probably use this;
 */
class IWorldObserver
{
public:
  virtual ~IWorldObserver() {}
  
  /**
   * This is called when the navMesh has changed. Used by pathfinder helper
   */
  virtual void onNavMeshQueryChange(dtNavMeshQuery *) {}
  
  virtual void onEntitySpawn(std::shared_ptr<class GameEntity>) {}
  
  /**
   * Called by the world before stopping. Object should use this method to unregister themselves
   */
  virtual void onWorldStop() {}
  
};

#endif	/* IWORLDOBSERVER_HPP */

