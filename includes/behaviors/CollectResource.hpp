/* 
 * File:   CollectResource.hpp
 * Author: xaqq
 *
 * Created on December 11, 2013, 7:54 PM
 */

#pragma once

#include "BehaviorTree.h"

namespace Behaviors
{
  /**
   * Routine that collects resource point from an ResourceEntity.
   * This routine returns BT_RUNNING until the resource is collected entirely.
   */
class CollectResource : public BehaviorTree::BehaviorTreeNode
{
public:
  CollectResource();
  CollectResource(const CollectResource& orig) = delete;
  virtual ~CollectResource();
  
  virtual BehaviorTree::BEHAVIOR_STATUS execute(void *agent) override;
  virtual void init(void *agent) override;
private:
};
}