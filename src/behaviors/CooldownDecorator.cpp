/* 
 * File:   CooldownDecorator.cpp
 * Author: xaqq
 * 
 * Created on December 11, 2013, 7:54 PM
 */

#include "behaviors/CooldownDecorator.hpp"
#include "world/ResourceEntity.hpp"
#include "Log.hpp"

using namespace BehaviorTree;
using namespace Behaviors;

CooldownDecorator::CooldownDecorator(Milliseconds cooldown, BehaviorTreeNode *child) : Decorator(child),
elapsed_(0),
cooldown_(cooldown) { }

CooldownDecorator::~CooldownDecorator() { }

BEHAVIOR_STATUS CooldownDecorator::execute(void *agent)
{
  if (elapsed_ + deltaTime() > cooldown_)
    {
      elapsed_ = Milliseconds(0);
      return child_->execute(agent);
    }
  else
    {
      elapsed_ += deltaTime();
    }
  return BT_RUNNING;
}

void CooldownDecorator::init(void *agent)
{
  DEBUG("INIT BEHAVIOR CooldownDecorator");
}