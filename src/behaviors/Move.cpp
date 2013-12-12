/* 
 * File:   Move.cpp
 * Author: xaqq
 * 
 * Created on December 11, 2013, 7:54 PM
 */

#include "behaviors/Move.hpp"
#include "world/MovableEntity.hpp"
#include "Log.hpp"

using namespace Behaviors;

Move::Move() { }

Move::~Move() { }

BehaviorTree::BEHAVIOR_STATUS Move::execute(void *agent)
{
  MovableEntity *e = reinterpret_cast<MovableEntity *>(agent);
  btVector3 dst(deltaTime().count() * e->velocity(), 0, 0);
  btMatrix3x3 m(e->transform().getRotation());

  dst = m * dst;
  DEBUG("Move:" << dst[0] << ", " << dst[1] << ", " << dst[2]);
  e->translate(dst);
  return BehaviorTree::BT_RUNNING;
}

void Move::init(void *agent)
{
  DEBUG("INIT BEHAVIOR Move");
}