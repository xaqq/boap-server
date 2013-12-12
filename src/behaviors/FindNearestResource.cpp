/* 
 * File:   FindNearestResource.cpp
 * Author: xaqq
 * 
 * Created on December 11, 2013, 7:54 PM
 */

#include "behaviors/FindNearestResource.hpp"
#include "world/ResourceEntity.hpp"
#include "Log.hpp"

using namespace Behaviors;

FindNearestResource::FindNearestResource() { }

FindNearestResource::~FindNearestResource() { }

BehaviorTree::BEHAVIOR_STATUS FindNearestResource::execute(void *agent)
{
  GameEntity *e = reinterpret_cast<GameEntity *> (agent);
  btScalar dist = -1.f;
  for (auto entity : e->world().entities())
    {
      std::shared_ptr<ResourceEntity> resource = std::dynamic_pointer_cast<ResourceEntity > (entity);
      if (resource)
        {
          btVector3 p = resource->position();
          if (dist > p.distance2(e->position()) || dist == -1.f)
            {
              dist = p.distance2(e->position());
              e->movement().setDestination(resource->position());
              e->target(resource);
            }
        }
    }
  if (dist >= 0)
    {
      INFO("Found and set a  target resource");
    return BehaviorTree::BT_SUCCESS;
    }
  ERROR("NO RESOURCE :(");
  return BehaviorTree::BT_FAILURE;
  ;
}

void FindNearestResource::init(void *agent)
{
  DEBUG("INIT BEHAVIOR FindNearestResource");
}