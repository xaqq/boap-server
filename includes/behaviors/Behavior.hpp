/* 
 * File:   Behavior.hpp
 * Author: xaqq
 *
 * Created on December 11, 2013, 7:38 PM
 */

#ifndef BEHAVIOR_HPP
#define	BEHAVIOR_HPP

#include "BehaviorTree.h"

namespace BehaviorTree
{
    class ParallelNode;
}

class Behavior
{
public:
    Behavior();
    Behavior(const Behavior& orig) = delete;
    virtual ~Behavior();

    bool update(void *param);

    void brain(BehaviorTree::ParallelNode *node)
    {
        delete brain_;
        brain_ = node;
    }

    BehaviorTree::ParallelNode *brain()
    {
        return brain_;
    }

private:
    BehaviorTree::ParallelNode *brain_;
};

#endif	/* BEHAVIOR_HPP */

