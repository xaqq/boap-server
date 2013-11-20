/* 
 * File:   NavMeshBuilder.hpp
 * Author: xaqq
 *
 * Created on November 17, 2013, 1:05 PM
 */

#ifndef NAVMESHBUILDER_HPP
#define	NAVMESHBUILDER_HPP

#include "RecastConverter.hpp"
#include "Recast.h"

/**
 * Load polygons from hardcoded input file
 */
class NavMeshBuilder
{

  enum SamplePolyFlags
  {
    MY_POLYFLAGS_WALK = 0x01, // Ability to walk (ground, grass, road)
    SAMPLE_POLYFLAGS_SWIM = 0x02, // Ability to swim (water).
    SAMPLE_POLYFLAGS_DOOR = 0x04, // Ability to move through doors.
    SAMPLE_POLYFLAGS_JUMP = 0x08, // Ability to jump.
    SAMPLE_POLYFLAGS_DISABLED = 0x10, // Disabled polygon
    SAMPLE_POLYFLAGS_ALL = 0xffff // All abilities.
  };

public:
  NavMeshBuilder(const char *sourceFilePath);
  NavMeshBuilder(const NavMeshBuilder& orig);
  virtual ~NavMeshBuilder();

  bool build();
public:
  class rcContext *m_ctx;
  class InputGeom *m_geom;
  class dtNavMesh* m_navMesh;
  class dtNavMeshQuery* m_navQuery;

  bool m_keepInterResults;
  float m_totalBuildTimeMs;

  unsigned char* m_triareas;
  rcHeightfield* m_solid;
  rcCompactHeightfield* m_chf;
  rcContourSet* m_cset;
  rcPolyMesh* m_pmesh;
  rcConfig m_cfg;
  rcPolyMeshDetail* m_dmesh;


  //config
  float m_cellSize;
  float m_cellHeight;
  float m_agentMaxSlope;
  float m_agentHeight;
  float m_agentMaxClimb;
  float m_agentRadius;
  float m_edgeMaxLen;
  float m_edgeMaxError;
  float m_regionMinSize;
  float m_regionMergeSize;
  int m_vertsPerPoly;
  float m_detailSampleDist;
  float m_detailSampleMaxError;
  bool m_monotonePartitioning;
};

#endif	/* NAVMESHBUILDER_HPP */

