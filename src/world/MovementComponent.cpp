/* 
 * File:   MovementComponent.cpp
 * Author: xaqq
 * 
 * Created on December 11, 2013, 8:50 PM
 */

#include "world/GameEntity.hpp"
#include "world/MovementComponent.hpp"

MovementComponent::MovementComponent(GameEntity &e) : me_(e),
pathHelper_(e, nullptr)
{

  me_.world().registerOberserver(&pathHelper_);
  pathHelper_.onNavMeshQueryChange(me_.world().navMeshQuery());
  velocity_ = 1;
}

MovementComponent::~MovementComponent() { }

const btVector3 &MovementComponent::destination() const
{
  return destination_;
}

bool MovementComponent::setDestination(btVector3 dest)
{
  destination_ = dest;
  return pathHelper_.findPath(me_.position(), destination_);
}

bool MovementComponent::setDestination(float x, float y, float z)
{
  destination_ = btVector3(x, y, z);
  return pathHelper_.findPath(me_.position(), destination_);
}

bool MovementComponent::destinationReached()
{
  if (me_.transform().getOrigin().distance2(destination_) < 0.001)
    {
      return true;
    }
  return false;
}

btVector3 MovementComponent::nextPoint()
{
  if (pathHelper_.path().isUsable())
    {
      return pathHelper_.nextCorner();
      ;
    }
  return me_.position();
}

bool MovementComponent::positionUpdated()
{
  pathHelper_.updatePosition(me_.position());
  return true;
}