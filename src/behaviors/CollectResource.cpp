/* 
 * File:   CollectResource.cpp
 * Author: xaqq
 * 
 * Created on December 11, 2013, 7:54 PM
 */

#include "behaviors/CollectResource.hpp"
#include "world/GameEntity.hpp"
#include "world/ResourceEntity.hpp"
#include "Log.hpp"

using namespace BehaviorTree;
using namespace Behaviors;

CollectResource::CollectResource() { }

CollectResource::~CollectResource() { }

BehaviorTree::BEHAVIOR_STATUS CollectResource::execute(void *agent)
{
  GameEntity *e = reinterpret_cast<GameEntity *> (agent);

  std::shared_ptr<ResourceEntity> resource = std::dynamic_pointer_cast<ResourceEntity>(e->target());

  if (resource)
    {
      int qtCollected = resource->collect(e->toSharedPtr(), 10);
      INFO("Collected " << qtCollected);

      if (!qtCollected)
        return BT_FAILURE; 
      if (qtCollected == 10 && resource->quantity() == 0) // resource is out
        return BT_SUCCESS;
      if (qtCollected < 10) // we took as much as possible, resource is out
        return BT_SUCCESS;
      return BT_RUNNING;
    }
  else
    {
      DEBUG("No resource targeted");
    }
  return BehaviorTree::BT_FAILURE;
}

void CollectResource::init(void *agent)
{
  DEBUG("INIT BEHAVIOR CollectResource");
}