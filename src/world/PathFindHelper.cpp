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
#include "world/PathFindResult.hpp"

PathFindHelper::PathFindHelper(MovableEntity &e, dtNavMeshQuery *q)
: entity_(e),
query_(q),
isCacheValid_(false)
{
  corridor_ = new dtPathCorridor();
  corridor_->init(1024);
}

PathFindHelper::~PathFindHelper()
{
  delete corridor_;
}

bool PathFindHelper::findPath(const btVector3 &start_pos, const btVector3 &end_pos)
{
  PathFindResult result;
  if (!query_)
    {
      WARN("findPath called but the path helper object has no navmesh query -- yet");
      return false;
    }
  float searchDst[] = {0.5, 0.5, 0.5};
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
      result.status_ = PathFindResult::Status::NO_START;
      return false;
    }
  result.start_ = start_pos;

  st = query_->findNearestPoly(reinterpret_cast<const float *> (&end_pos), searchDst, new dtQueryFilter(), &end, points);
  if (dtStatusFailed(st) || end == 0)
    {
      WARN("FAILED TO FIND END POLYGONE");
      result.status_ = PathFindResult::Status::NO_END;
      return false;
    }

  st = query_->findPath(start, end, start_pos, end_pos, new dtQueryFilter(), path, &pathCount, 1000);
  if (dtStatusFailed(st))
    {
      WARN("FAILED TO FIND PATH");
      result.status_ = PathFindResult::Status::NO_PATH;
      return false;
    }

  corridor_->reset(start, reinterpret_cast<const float *> (&start_pos));
  corridor_->setCorridor(reinterpret_cast<const float *> (&end_pos), path, pathCount);

  float cornerVerts[3 * 100];
  unsigned char cornerFlags[100];
  dtPolyRef cornerPolys[100];
  int nbCorners;
  nbCorners = corridor_->findCorners(cornerVerts, cornerFlags, cornerPolys, 99, query_, new dtQueryFilter());

  for (int i = 0; i < nbCorners; ++i)
    {
      result.corners_.push_back(btVector3(cornerVerts[i * 3], cornerVerts[i * 3 + 1], cornerVerts[i * 3 + 2]));
    }
  result.status_ = PathFindResult::Status::VALID;
  path_ = result;
  isCacheValid_ = true;
  return true;
}

void PathFindHelper::updatePosition(const btVector3 & pos)
{
  float newPos[3] = {pos[0], pos[1], pos[2]};
  corridor_->movePosition(newPos, query_, new dtQueryFilter());

  isCacheValid_ = false;
}

void PathFindHelper::onNavMeshQueryChange(dtNavMeshQuery * query)
{
  query_ = query;
  isCacheValid_ = false;
}

bool PathFindHelper::isUsable() const
{
  return isCacheValid_ || query_;
}

const PathFindResult &PathFindHelper::path()
{
  if (isCacheValid_)
    return path_;
  findPath(entity_.position(), entity_.destination());
  return path_;
}