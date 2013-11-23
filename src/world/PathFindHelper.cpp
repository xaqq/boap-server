/* 
 * File:   PathFindHelper.cpp
 * Author: xaqq
 * 
 * Created on November 18, 2013, 4:44 PM
 */

#include "world/PathFindHelper.hpp"
#include "Log.hpp"
#include "world/NavMeshBuilder.hpp"
#include "world/MovableEntity.hpp"

PathFindHelper::PathFindHelper(MovableEntity &e, dtNavMeshQuery *q)
: entity_(e),
query_(q),
isCacheValid_(false)
{
  corridor_ = new dtPathCorridor();
  corridor_->init(1024);
}

PathFindHelper::~PathFindHelper() { }

bool PathFindHelper::findPath(const btVector3 &start_pos, const btVector3 &end_pos)
{
  if (!query_)
    {
      WARN("findPath called but the path helper object has no navmesh query -- yet");
      return false;
    }
  float searchDst[] = {5, 5, 5};
  float points[] = {0, 0, 0};
  dtPolyRef start = 0;
  dtPolyRef end = 0;
  dtStatus st;
  dtPolyRef path[1000];
  int pathCount = 0;

  st = query_->findNearestPoly(reinterpret_cast<const float *> (&start_pos), searchDst, new dtQueryFilter(), &start, points);
  if (dtStatusFailed(st) || start == 0)
    {
      WARN("FAILED TO FIND START POLYGONE");
      return false;
    }

  st = query_->findNearestPoly(reinterpret_cast<const float *> (&end_pos), searchDst, new dtQueryFilter(), &end, points);
  if (dtStatusFailed(st) || end == 0)
    {
      WARN("FAILED TO FIND END POLYGONE");
      return false;
    }

  st = query_->findPath(start, end, start_pos, end_pos, new dtQueryFilter(), path, &pathCount, 1000);
  if (dtStatusFailed(st))
    {
      WARN("FAILED TO FIND PATH");
      return false;
    }

  corridor_->reset(start, reinterpret_cast<const float *> (&start_pos));
  corridor_->setCorridor(reinterpret_cast<const float *> (&end_pos), path, pathCount);

  float cornerVerts[3 * 100];
  unsigned char cornerFlags[100];
  dtPolyRef cornerPolys[100];
  int nbCorners;
  nbCorners = corridor_->findCorners(cornerVerts, cornerFlags, cornerPolys, 99, query_, new dtQueryFilter());

  if (nbCorners >= 1)
    {
      memcpy(static_cast<void *> (nextCorner_), cornerVerts, sizeof (nextCorner_));
    }
  int i = 0;
  for (auto f : cornerVerts)
    {
      if (i >= nbCorners)
        continue;
      DEBUG(f << ", ");
      i++;
      if (i % 3 == 0)
        {
          DEBUG("new point");
        }
    }

  DEBUG("Found path with nb_polygone = " << pathCount);
  DEBUG(path[pathCount - 1]);

  DEBUG("Points:" << points[0] << ", " << points[1] << ", " << points[2]);
  if (nbCorners)
    DEBUG("poly:" << cornerPolys[nbCorners - 1]);
  return true;
}

btVector3 PathFindHelper::nextCorner()
{
  if (!isCacheValid_)
    {
      if (!query_)
        {
          WARN("PathFindHelper cache invalid and there is no query object available");
          return
          {
            0, 0, 0
          };
        }
      findPath(entity_.position(), entity_.destination());
      isCacheValid_ = true;
    }
  return btVector3(nextCorner_[0], nextCorner_[1], nextCorner_[2]);
}

void PathFindHelper::updatePosition(const btVector3 & pos)
{
  float newPos[3] = {pos[0], pos[1], pos[2]};
  corridor_->movePosition(newPos, query_, new dtQueryFilter());

  isCacheValid_ = false;
}

void PathFindHelper::onNavMeshQueryChange(dtNavMeshQuery * query)
{
  DEBUG("Query updated: " << query);
  query_ = query;
  isCacheValid_ = false;
}

bool PathFindHelper::isUsable() const
{
  return isCacheValid_ || query_;
}