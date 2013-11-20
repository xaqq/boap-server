#pragma once
#include <bullet/btBulletDynamicsCommon.h>
#include <array>
#include <list>
#include <string>
#include <vector>

class GameEntity;
class RecastConverter
{
public:
  RecastConverter() {}

  void addEntity(GameEntity *e);
  
  std::string genDataDump();

private:
  std::list<GameEntity *> entities_;

  // All vertices
  std::vector<btVector3> vertices_;
  /**
   * Index of 3 vertices of each triangle
   */
  std::list<std::array<int, 3>> trianglesVerticesIndex_;
};
