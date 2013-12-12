/* 
 * File:   Behavior.cpp
 * Author: xaqq
 * 
 * Created on December 11, 2013, 7:38 PM
 */

#include "behaviors/Behavior.hpp"
#include "BehaviorTree.h"
#include "world/GameEntity.hpp"
#include "behaviors/Speak.hpp"
#include "behaviors/Move.hpp"

using namespace BehaviorTree;

Behavior::Behavior() :
brain_(new ParallelNode(/*FAIL_ON_ALL, SUCCEED_ON_ONE*/))
{
  brain_->addChild((new RepeatNode(-1))->addChild(new Behaviors::Speak("lama")))
           ->addChild(new Behaviors::Move());
}

Behavior::~Behavior()
{
  DEBUG("DELETING BEHAVIOR");
  delete brain_;
}

void Behavior::update(GameEntity *e)
{
  switch (brain_->execute(e))
    {
    case BT_FAILURE:
      WARN("Behavior Tree failure");
      break;
    case BT_SUCCESS:
      WARN("Behavior tree success");
      break;
    case BT_RUNNING:
      WARN("Behavior tree running");
      break;
    }
}

