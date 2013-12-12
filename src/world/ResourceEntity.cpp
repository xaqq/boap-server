/* 
 * File:   ResourceEntity.cpp
 * Author: xaqq
 * 
 * Created on December 3, 2013, 1:34 PM
 */

#include "world/ResourceEntity.hpp"
#include <functional>

ResourceEntity::ResourceEntity(WorldFacade &world, std::shared_ptr<btCollisionShape> shape) :
GameEntity(world, shape),
quantity_(95) { }

ResourceEntity::~ResourceEntity() { }

int ResourceEntity::collect(std::shared_ptr<GameEntity> collector, int qt)
{
  if (qt < quantity_)
    {
      quantity_ -= qt;
      return qt;
    }
  qt = quantity_;
  quantity_ = 0;
  dispatch(std::bind(&IEntityObserver::outOfResource, std::placeholders::_1, std::dynamic_pointer_cast<ResourceEntity > (shared_from_this())));

  return qt;
}

int ResourceEntity::quantity() const
{
  return quantity_;
}