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
#include "behaviors/MoveToDestination.hpp"
#include "behaviors/FindNearestResource.hpp"
#include "behaviors/CollectResource.hpp"
#include "behaviors/CooldownDecorator.hpp"

using namespace BehaviorTree;
using namespace Behaviors;

Behavior::Behavior() :
brain_(new ParallelNode(/*FAIL_ON_ALL, SUCCEED_ON_ONE*/))
{
  // brain_->addChild((new RepeatNode(-1))->addChild(new Behaviors::Speak("lama")))
  //        ->addChild(new Behaviors::Move());

  ProbabilityNode *sayNode = new ProbabilityNode();
  sayNode->addChild(new Speak("Lama"), 2);
  sayNode->addChild(new Speak("Kikoo :D"), 1);

  brain_->addChild((new RepeatNode(-1))
                   ->addChild(((new SequentialNode())
                               ->addChild(new FindNearestResource())
                               ->addChild(new Speak("Going toward my new destination !"))
                               ->addChild(new MoveToDestination())
                               ->addChild(new CooldownDecorator(Milliseconds(2000), new CollectResource()))
                               ->addChild(new Speak("Done collecting resources")))))
          ->addChild((new RepeatNode(-1))
                     ->addChild(new CooldownDecorator(Milliseconds(10000), sayNode)));
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
      // WARN("Behavior tree running");
      break;
    }
}

