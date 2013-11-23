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
   * Each element of the list is a polygone; the vector represents the idx of its vertices;
   */
  std::list<std::vector<int>> polyVerticesIdx_;
};
