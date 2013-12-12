/* 
 * File:   Move.cpp
 * Author: xaqq
 * 
 * Created on December 11, 2013, 7:54 PM
 */

#include "behaviors/Move.hpp"
#include "world/GameEntity.hpp"
#include "Log.hpp"

using namespace Behaviors;

Move::Move() { }

Move::~Move() { }

BehaviorTree::BEHAVIOR_STATUS Move::execute(void *agent)
{
  GameEntity *e = reinterpret_cast<GameEntity *>(agent);
  
  if (!e->movement().canMove())
    return BehaviorTree::BT_FAILURE;
  
  btVector3 destination = e->movement().nextPoint();
  float forward = (deltaTime().count() / 1000.0f) * e->movement().velocity();;
  btVector3 dst = e->movement().nextPoint() - e->position();;
  btScalar reqDist = e->movement().nextPoint().distance2(e->position());

  dst.normalize();
  dst = dst * forward;
  btScalar translatDist = e->position().distance2(e->position() + dst);
  // make sure we dont go too far
  if (translatDist > reqDist)
    e->translate(e->movement().nextPoint() - e->position());
  else
    e->translate(dst);
  e->movement().positionUpdated();
  return BehaviorTree::BT_SUCCESS;;
}

void Move::init(void *agent)
{
  DEBUG("INIT BEHAVIOR Move");
}