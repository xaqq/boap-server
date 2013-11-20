#include <sstream>
#include <array>
#include "world/RecastConverter.hpp"
#include "world/GameEntity.hpp"


void RecastConverter::addEntity(GameEntity *e)
{
  entities_.push_back(e);
}

std::string RecastConverter::genDataDump()
{
  std::stringstream ss;
  int		    idx;

  for (auto e : entities_)
    {
      auto triangles = e->getTriangles();
      for (auto triangle : triangles)
	{
	  std::array<int, 3> verticesIdx;
	  for (int i = 0; i < 3; ++i)
	    {
	      vertices_.push_back(triangle[i]);
	      idx = vertices_.size();
	      verticesIdx[i] = idx;
	    }
	  trianglesVerticesIndex_.push_back(verticesIdx);
	}
    }

  for (auto vertice : vertices_)
    {
      ss << "v " << vertice[0] << " " << vertice[1] << " " << vertice[2] << std::endl;
    }
  for (auto triangle : trianglesVerticesIndex_)
    {
      ss << "f " << triangle[0] << " " << triangle[1] << " " << triangle[2] << std::endl;
    }
  return ss.str();
}
