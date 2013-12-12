/* 
 * File:   PathFindHelper.hpp
 * Author: xaqq
 *
 * Created on November 18, 2013, 4:44 PM
 */

#ifndef PATHFINDHELPER_HPP
#define	PATHFINDHELPER_HPP

#include "Recast.h"
#include "DetourCommon.h"
#include "DetourPathCorridor.h"
#include <bullet/btBulletCollisionCommon.h>
#include "world/IWorldObserver.hpp"
#include "PathFindResult.hpp"

/**
 * Path finding helper; Used by entity that requires pathfinding
 */
class PathFindHelper : public IWorldObserver
{
public:
  PathFindHelper(class MovableEntity &e, dtNavMeshQuery *q);
  PathFindHelper(const PathFindHelper&) = delete;
  virtual ~PathFindHelper();

  /**
   * Find the path and update the internal helper state so that nextCorner() will return
   * a new usable value.
   * @param start start position
   * @param end end position;
   */
  bool findPath(const btVector3 &start, const btVector3 &end);
  btVector3 nextCorner();

  /**
   * Feed the new agent position back to the path helper corridor
   */
  void updatePosition(const btVector3 &pos);

  void onNavMeshQueryChange(dtNavMeshQuery *query) override;
  
  
  bool isUsable() const;
  
  /**
   * Returns a reference to the current PathFindResult object.
   * This method will re-plan the path if the cache becomes invalid.
   * @return A reference to the path
   */
  const PathFindResult &path();
private:
  /**
   * A reference to the entity using this helper.
   */
  MovableEntity &entity_;
  
  dtPathCorridor *corridor_;
  dtNavMeshQuery *query_;

  /**
   * The current path result.
   */
  PathFindResult path_;
  
  /**
   * Whereas the cache is valid or not.
   */
  bool isCacheValid_;
};

#endif	/* PATHFINDHELPER_HPP */

