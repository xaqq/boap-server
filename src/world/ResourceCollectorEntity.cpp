/* 
 * File:   ResourceCollectorEntity.cpp
 * Author: xaqq
 * 
 * Created on December 3, 2013, 1:44 PM
 */

#include "world/ResourceCollectorEntity.hpp"
#include "Log.hpp"

ResourceCollectorEntity::ResourceCollectorEntity(WorldFacade &world, std::shared_ptr<btCollisionShape> shape) :
MovableEntity(world, shape),
searchCooldown_(5000),
collectCooldown_(1300)
{
  movement().velocity(18);
}

ResourceCollectorEntity::~ResourceCollectorEntity() { }

bool ResourceCollectorEntity::findNewTarget()
{
  if (targetResource_.lock())
    return true;
  btScalar dist = -1.f;
  for (auto e : world_.entities())
    {
      std::shared_ptr<ResourceEntity> resource = std::dynamic_pointer_cast<ResourceEntity > (e);
      if (resource)
        {
          btVector3 p = resource->position();
          if (dist > p.distance2(position()) || dist == -1.f)
            {
              dist = p.distance2(position());
              targetResource_ = resource;
            }
        }
    }
  if (targetResource_.lock())
    return true;
  return false;
}

void ResourceCollectorEntity::update(Milliseconds ms)
{
  behavior_.update(this);
  return;
  if (searchCooldown_ + ms > Milliseconds(5000))
    {
      DEBUG("Has a target? : " << findNewTarget());
      auto target = targetResource_.lock();
      if (target)
        {
          DEBUG("Set destination!");
          setDestination(target->position());
        }
      searchCooldown_ = Milliseconds(0);
    }
  else
    {
      searchCooldown_ += ms;
    }

  if (destinationReached())
    {
      if (collectCooldown_ + ms > Milliseconds(1300))
        {
          if (auto target = targetResource_.lock())
            {
              int c = target->collect(shared_from_this(), 10);
              DEBUG("Dest reached, collecting : " << c);
              if (c && rand() % 2 == 0)
                {
//                  DEBUG("SPAWN FRIEND");
//                  auto f = world_.spawn(4);
//                  if (f)
//                    {
//                      f->setPosition(rand() % 100, 0, rand() % 100);
//                    }
                }
              collectCooldown_ = Milliseconds(0);
            }
        }
      else
        collectCooldown_ += ms;
      return;
    }

  if (targetResource_.lock())
    {
      moveTowardTarget();
    }
}