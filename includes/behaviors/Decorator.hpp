/* 
 * File:   Decorator.hpp
 * Author: xaqq
 *
 * Created on December 11, 2013, 11:20 PM
 */

#ifndef DECORATOR_HPP
#define	DECORATOR_HPP

#include "BehaviorTree.h"

namespace Behaviors
{

  /**
   * Base decorator for node
   * @param child
   */
  class Decorator : public BehaviorTree::BehaviorTreeNode
  {
  public:

    Decorator(BehaviorTree::BehaviorTreeNode *child) : child_(child) { };
    Decorator(const Decorator&) = delete;
    virtual ~Decorator()
    {
      delete child_;
    }

    /**
     * Do something here (like timer, custom check) and call the child_
     * @param agent
     * @return Status
     */
    virtual BehaviorTree::BEHAVIOR_STATUS execute(void *agent) = 0;
    virtual void init(void *agent) = 0;

  protected:
    BehaviorTree::BehaviorTreeNode *child_;
  };
}

#endif	/* DECORATOR_HPP */

