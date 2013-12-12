/* 
 * File:   MovableEntity.cpp
 * Author: xaqq
 * 
 * Created on November 18, 2013, 11:04 PM
 */

#include "Log.hpp"
#include "world/MovableEntity.hpp"
#include "world/WorldFacade.hpp"

MovableEntity::MovableEntity(WorldFacade &world, std::shared_ptr<btCollisionShape> shape) : GameEntity(world, shape),
isMoving_(false),
pathHelper_(*this, nullptr)
{
  velocity_ = 1;
  world_.registerOberserver(&pathHelper_);
  pathHelper_.onNavMeshQueryChange(world_.navMeshQuery());
}

MovableEntity::~MovableEntity()
{
  DEBUG("Movable entity destroyed");
  world_.unregisterObserver(&pathHelper_);
}

const btVector3 &MovableEntity::destination() const
{
  return destination_;
}

bool MovableEntity::setDestination(btVector3 dest)
{
  destination_ = dest;
  return pathHelper_.findPath(position(), destination_);
}

bool MovableEntity::setDestination(float x, float y, float z)
{
  destination_ = btVector3(x, y, z);
  return pathHelper_.findPath(position(), destination_);
}

bool MovableEntity::moveTowardTarget()
{
  DEBUG("St :" << (int)pathHelper_.path().status());
  if (!pathHelper_.path().isUsable())
    return false;
  float forward = (deltaTime().count() / 1000.0f) * velocity_;
  DEBUG("Forward " << forward << ";Delta time = " << deltaTime().count() <<
          "Distance left: " << pathHelper_.path().length());
  btVector3 dst = pathHelper_.path().nextCorner() - transform().getOrigin();
  btScalar reqDist = pathHelper_.path().nextCorner().distance2(transform().getOrigin());

  dst.normalize();
  DEBUG("PREMove:" << dst[0] << ", " << dst[1] << ", " << dst[2]);
  dst = dst * forward;

  btScalar translatDist = transform().getOrigin().distance2(transform().getOrigin() + dst);

  // make sure we dont go too far
  if (translatDist > reqDist)
    translate(pathHelper_.path().nextCorner() - transform().getOrigin());
  else
    translate(dst);
  DEBUG("Move:" << dst[0] << ", " << dst[1] << ", " << dst[2]);
  pathHelper_.updatePosition(transform().getOrigin());
  DEBUG("New position:" << transform().getOrigin()[0] << ", " << transform().getOrigin()[1] << ", " << transform().getOrigin()[2]);
  return true;
}

bool MovableEntity::move()
{
  btVector3 dst(deltaTime().count() * velocity_, 0, 0);
  btMatrix3x3 m(transform().getRotation());

  dst = m * dst;
  DEBUG("Move:" << dst[0] << ", " << dst[1] << ", " << dst[2]);
  translate(dst);
  return true;
}

void MovableEntity::update(Milliseconds diff)
{
  if (pathHelper_.isUsable() && isMoving_)
    {
      if (destinationReached())
        {
          DEBUG("I REACHED MY TARGET DESTINATION");
          setDestination(rand() % 5, rand() % 5, rand() % 5);
        }
      else
        moveTowardTarget();
    }
}

bool MovableEntity::destinationReached()
{
  if (transform().getOrigin().distance2(destination_) < 0.001)
    {
      return true;
    }
  return false;
}