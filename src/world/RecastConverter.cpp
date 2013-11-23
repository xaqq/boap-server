#include <sstream>
#include <array>
#include "world/RecastConverter.hpp"
#include "world/GameEntity.hpp"
#include "Log.hpp"

void RecastConverter::addEntity(GameEntity *e)
{
  entities_.push_back(e);
}

std::string RecastConverter::genDataDump()
{
  std::stringstream ss;
  int idx;

  for (auto e : entities_)
    {
      if (!e->affectNavMesh())
        continue;
      auto polygones = e->getPolygones();
      for (auto poly : polygones)
        {
          std::vector<int> verticesIdx;
          for (int i = 0; i < poly.size(); ++i)
            {
              vertices_.push_back(poly[i]);
              idx = vertices_.size();
              verticesIdx.push_back(idx);
            }
          polyVerticesIdx_.push_back(verticesIdx);
        }
    }

  for (auto vertice : vertices_)
    {
      ss << "v " << vertice[0] << " " << vertice[1] << " " << vertice[2] << std::endl;
    }
  for (auto poly : polyVerticesIdx_)
    {
      ss << "f ";
      for (int i = 0; i < poly.size(); ++i)
        ss << poly[i] << " ";
      ss << std::endl;
    }
  return ss.str();
}
