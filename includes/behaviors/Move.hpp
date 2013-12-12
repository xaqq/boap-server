/* 
 * File:   Move.hpp
 * Author: xaqq
 *
 * Created on December 11, 2013, 7:54 PM
 */

#pragma once

#include "BehaviorTree.h"

namespace Behaviors
{
  /**
   * Low level routine that move an entity forward;
   */
class Move : public BehaviorTree::BehaviorTreeNode
{
public:
  Move();
  Move(const Move& orig) = delete;
  virtual ~Move();
  
  virtual BehaviorTree::BEHAVIOR_STATUS execute(void *agent) override;
  virtual void init(void *agent) override;
private:
  std::string str_;
};
}

