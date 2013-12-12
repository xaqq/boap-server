#include "behaviors/MoveToDestination.hpp"
#include "behaviors/Decorator.hpp"
#include "behaviors/Move.hpp"
#include "world/GameEntity.hpp"
#include "Log.hpp"

using namespace BehaviorTree;
using namespace Behaviors;

MoveToDestination::MoveToDestination() : Decorator(static_cast<BehaviorTreeNode *> (new Move())) { }

BEHAVIOR_STATUS MoveToDestination::execute(void *agent)
{
  GameEntity *e = reinterpret_cast<GameEntity *> (agent);
//  DEBUG("POS: " << e->position()[0] << " " << e->position()[1] << " " << e->position()[2] << " ");
//  DEBUG("DEST: " << e->movement().destination()[0] << " " << 
//         e->movement().destination()[1] << " "  << e->movement().destination()[2] << " ");
  if (e->movement().destinationReached())
    {
      INFO("Destination Reached...");
      return BT_SUCCESS;
    }
  BEHAVIOR_STATUS st = child_->execute(agent);

  if (st == BT_SUCCESS)
    return BT_RUNNING;
  return st;
}

void MoveToDestination::init(void *agent)
{
  child_->init(agent);
}