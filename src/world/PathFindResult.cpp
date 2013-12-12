/* 
 * File:   PathFindResult.cpp
 * Author: xaqq
 * 
 * Created on December 4, 2013, 4:34 PM
 */

#include <bullet/LinearMath/btVector3.h>
#include "Log.hpp"
#include "world/PathFindResult.hpp"

PathFindResult::PathFindResult() : status_(Status::UNKOWN) { }

PathFindResult::PathFindResult(const PathFindResult& orig) { }

PathFindResult::~PathFindResult() { }

PathFindResult::Status PathFindResult::status() const
{
  return status_;
}

bool PathFindResult::isUsable() const
{
  if (status_ == Status::TOO_LONG || status_ == Status::VALID)
    return true;
  return false;
}

float PathFindResult::length() const
{
  float res = 0.f;

  if (!isUsable())
    return 0;
  res += start_.distance(corners_[0]);
  for (auto it = corners_.begin(); (it + 1) != corners_.end(); ++it)
    {
      res += (*it).distance(*(it + 1));
    }
  return res;
}

const btVector3 &PathFindResult::nextCorner() const
{
  return corners_.at(0);
}