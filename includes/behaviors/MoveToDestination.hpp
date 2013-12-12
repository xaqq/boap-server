/* 
 * File:   MoveToDestination.hpp
 * Author: xaqq
 *
 * Created on December 11, 2013, 7:54 PM
 */

#pragma once

#include "behaviors/Decorator.hpp"

namespace Behaviors
{
  /**
   * Low level routine that move an entity forward;
   */
class MoveToDestination : public Decorator
{
public:
  MoveToDestination();
  MoveToDestination(const MoveToDestination& orig) = delete;
  virtual ~MoveToDestination() {};
  
  virtual BehaviorTree::BEHAVIOR_STATUS execute(void *agent) override;
  virtual void init(void *agent) override;
private:
};
}

