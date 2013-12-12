/* 
 * File:   CooldownDecorator.hpp
 * Author: xaqq
 *
 * Created on December 11, 2013, 7:54 PM
 */

#pragma once

#include "behaviors/Decorator.hpp"
#include "Clock.hpp"

namespace Behaviors
{
  /**
   * Cooldown decorator that prevent an action from being run too fast.
   */
class CooldownDecorator : public Decorator
{
public:
  CooldownDecorator(Milliseconds cooldown, BehaviorTreeNode *child);
  CooldownDecorator(const CooldownDecorator& orig) = delete;
  virtual ~CooldownDecorator();
  
  virtual BehaviorTree::BEHAVIOR_STATUS execute(void *agent) override;
  virtual void init(void *agent) override;
private:
  Milliseconds elapsed_;
  Milliseconds cooldown_;
};
}

