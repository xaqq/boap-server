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
pathHelper_(*this, nullptr)
{
  velocity_ = 1;
  world_.registerOberserver(&pathHelper_);
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

bool MovableEntity::setDestination(float x, float y, float z)
{
  destination_ = btVector3(x, y, z);
  return pathHelper_.findPath(position(), destination_);
}

bool MovableEntity::moveTowardTarget()
{
  float forward = (deltaTime().count() / 1000.0f) * velocity_;
  DEBUG("Forward " << forward << ";Delta time = " << deltaTime().count());
  btVector3 dst = pathHelper_.nextCorner() - transform().getOrigin();
  btScalar reqDist = pathHelper_.nextCorner().distance2(transform().getOrigin());

  dst.normalize();
  DEBUG("PREMove:" << dst[0] << ", " << dst[1] << ", " << dst[2]);
  dst = dst * forward;

  btScalar translatDist = transform().getOrigin().distance2(transform().getOrigin() + dst);

  // make sure we dont go too far
  if (translatDist > reqDist)
    translate(pathHelper_.nextCorner() - transform().getOrigin());
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
  if (pathHelper_.isUsable())
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
  if (transform().getOrigin().distance2(pathHelper_.nextCorner()) < 0.001)
    {
      return true;
    }
  return false;
}