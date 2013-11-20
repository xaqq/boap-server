/* 
 * File:   NavMeshBuilder.cpp
 * Author: xaqq
 * 
 * Created on November 17, 2013, 1:05 PM
 */

#include "Recast.h"
#include "DetourCommon.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshBuilder.h"
#include "DetourDebugDraw.h"
#include "world/NavMeshBuilder.hpp"
#include "world/InputGeom.h"
#include "Log.hpp"

NavMeshBuilder::NavMeshBuilder(const char *sourceFilePath)
{
  m_ctx = new rcContext(true);
  m_geom = new InputGeom();

  m_cellSize = 0.10f;
  m_cellHeight = 0.10f;
  m_agentMaxSlope = 45;

  m_agentHeight = 1;
  m_agentMaxClimb = 2;
  m_agentRadius = 0.1;
  m_edgeMaxLen = 3;
  m_edgeMaxError = 1;
  m_regionMinSize = 1;
  m_regionMergeSize = 8;
  m_vertsPerPoly = 6;
  m_detailSampleDist = 1;
  m_detailSampleMaxError = 1;
  m_monotonePartitioning = false;
  m_keepInterResults = false;

  m_navQuery = new dtNavMeshQuery();
  m_geom->loadMesh(m_ctx, sourceFilePath);
}

NavMeshBuilder::NavMeshBuilder(const NavMeshBuilder& orig) { }

NavMeshBuilder::~NavMeshBuilder() {
  delete m_ctx;
  delete m_geom;
  delete m_navQuery;
}

bool NavMeshBuilder::build()
{

  if (!m_geom || !m_geom->getMesh())
    {
      ERROR("buildNavigation: Input mesh is not specified.");
      return false;
    }

  const float* bmin = m_geom->getMeshBoundsMin();
  const float* bmax = m_geom->getMeshBoundsMax();
  const float* verts = m_geom->getMesh()->getVerts();
  const int nverts = m_geom->getMesh()->getVertCount();
  const int* tris = m_geom->getMesh()->getTris();
  const int ntris = m_geom->getMesh()->getTriCount();

  //
  // Step 1. Initialize build config.
  //

  DEBUG("here");

  // Init build configuration from GUI
  memset(&m_cfg, 0, sizeof (m_cfg));
  m_cfg.cs = m_cellSize;
  m_cfg.ch = m_cellHeight;
  m_cfg.walkableSlopeAngle = m_agentMaxSlope;
  m_cfg.walkableHeight = (int) ceilf(m_agentHeight / m_cfg.ch);
  m_cfg.walkableClimb = (int) floorf(m_agentMaxClimb / m_cfg.ch);
  m_cfg.walkableRadius = (int) ceilf(m_agentRadius / m_cfg.cs);
  m_cfg.maxEdgeLen = (int) (m_edgeMaxLen / m_cellSize);
  m_cfg.maxSimplificationError = m_edgeMaxError;
  m_cfg.minRegionArea = (int) rcSqr(m_regionMinSize); // Note: area = size*size
  m_cfg.mergeRegionArea = (int) rcSqr(m_regionMergeSize); // Note: area = size*size
  m_cfg.maxVertsPerPoly = (int) m_vertsPerPoly;
  m_cfg.detailSampleDist = m_detailSampleDist < 0.9f ? 0 : m_cellSize * m_detailSampleDist;
  m_cfg.detailSampleMaxError = m_cellHeight * m_detailSampleMaxError;



  // Set the area where the navigation will be build.
  // Here the bounds of the input mesh are used, but the
  // area could be specified by an user defined box, etc.
  rcVcopy(m_cfg.bmin, bmin);
  rcVcopy(m_cfg.bmax, bmax);
  rcCalcGridSize(m_cfg.bmin, m_cfg.bmax, m_cfg.cs, &m_cfg.width, &m_cfg.height);

  // Reset build times gathering.
  m_ctx->resetTimers();

  // Start the build process.	
  m_ctx->startTimer(RC_TIMER_TOTAL);

  DEBUG("Building navigation:");
  DEBUG(" - " << m_cfg.width << " x " << m_cfg.height << " cells");
  DEBUG(" - " << nverts / 1000.0f << "K verts, " << ntris / 1000.0f << "K tris");

  //
  // Step 2. Rasterize input polygon soup.
  //

  // Allocate voxel heightfield where we rasterize our input data to.
  m_solid = rcAllocHeightfield();
  if (!m_solid)
    {
      m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'solid'.");
      return false;
    }
  if (!rcCreateHeightfield(m_ctx, *m_solid, m_cfg.width, m_cfg.height, m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch))
    {
      m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not create solid heightfield.");
      return false;
    }

  // Allocate array that can hold triangle area types.
  // If you have multiple meshes you need to process, allocate
  // and array which can hold the max number of triangles you need to process.
  m_triareas = new unsigned char[ntris];
  if (!m_triareas)
    {
      m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'm_triareas' (%d).", ntris);
      return false;
    }

  // Find triangles which are walkable based on their slope and rasterize them.
  // If your input data is multiple meshes, you can transform them here, calculate
  // the are type for each of the meshes and rasterize them.
  memset(m_triareas, 0, ntris * sizeof (unsigned char));
  rcMarkWalkableTriangles(m_ctx, m_cfg.walkableSlopeAngle, verts, nverts, tris, ntris, m_triareas);
  rcRasterizeTriangles(m_ctx, verts, nverts, tris, m_triareas, ntris, *m_solid, m_cfg.walkableClimb);

  if (!m_keepInterResults)
    {
      delete [] m_triareas;
      m_triareas = 0;
    }

  //
  // Step 3. Filter walkables surfaces.
  //

  // Once all geoemtry is rasterized, we do initial pass of filtering to
  // remove unwanted overhangs caused by the conservative rasterization
  // as well as filter spans where the character cannot possibly stand.
  rcFilterLowHangingWalkableObstacles(m_ctx, m_cfg.walkableClimb, *m_solid);
  rcFilterLedgeSpans(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid);
  rcFilterWalkableLowHeightSpans(m_ctx, m_cfg.walkableHeight, *m_solid);


  //
  // Step 4. Partition walkable surface to simple regions.
  //

  // Compact the heightfield so that it is faster to handle from now on.
  // This will result more cache coherent data as well as the neighbours
  // between walkable cells will be calculated.
  m_chf = rcAllocCompactHeightfield();
  if (!m_chf)
    {
      ERROR("buildNavigation: Out of memory 'chf'.");
      return false;
    }
  if (!rcBuildCompactHeightfield(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid, *m_chf))
    {
      ERROR("buildNavigation: Could not build compact data.");
      return false;
    }

  if (!m_keepInterResults)
    {
      rcFreeHeightField(m_solid);
      m_solid = 0;
    }

  // Erode the walkable area by agent radius.
  if (!rcErodeWalkableArea(m_ctx, m_cfg.walkableRadius, *m_chf))
    {
      m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not erode.");
      return false;
    }

  // (Optional) Mark areas.
  const ConvexVolume* vols = m_geom->getConvexVolumes();
  for (int i = 0; i < m_geom->getConvexVolumeCount(); ++i)
    rcMarkConvexPolyArea(m_ctx, vols[i].verts, vols[i].nverts, vols[i].hmin, vols[i].hmax, (unsigned char) vols[i].area, *m_chf);

  if (m_monotonePartitioning)
    {
      // Partition the walkable surface into simple regions without holes.
      // Monotone partitioning does not need distancefield.
      if (!rcBuildRegionsMonotone(m_ctx, *m_chf, 0, m_cfg.minRegionArea, m_cfg.mergeRegionArea))
        {
          m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build regions.");
          return false;
        }
    }
  else
    {
      // Prepare for region partitioning, by calculating distance field along the walkable surface.
      if (!rcBuildDistanceField(m_ctx, *m_chf))
        {
          m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build distance field.");
          return false;
        }

      // Partition the walkable surface into simple regions without holes.
      if (!rcBuildRegions(m_ctx, *m_chf, 0, m_cfg.minRegionArea, m_cfg.mergeRegionArea))
        {
          m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build regions.");
          return false;
        }
    }

  //
  // Step 5. Trace and simplify region contours.
  //

  // Create contours.
  m_cset = rcAllocContourSet();
  if (!m_cset)
    {
      m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'cset'.");
      return false;
    }
  if (!rcBuildContours(m_ctx, *m_chf, m_cfg.maxSimplificationError, m_cfg.maxEdgeLen, *m_cset))
    {
      m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not create contours.");
      return false;
    }

  //
  // Step 6. Build polygons mesh from contours.
  //

  // Build polygon navmesh from the contours.
  m_pmesh = rcAllocPolyMesh();
  if (!m_pmesh)
    {
      m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'pmesh'.");
      return false;
    }
  if (!rcBuildPolyMesh(m_ctx, *m_cset, m_cfg.maxVertsPerPoly, *m_pmesh))
    {
      m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not triangulate contours.");
      return false;
    }

  //
  // Step 7. Create detail mesh which allows to access approximate height on each polygon.
  //

  m_dmesh = rcAllocPolyMeshDetail();
  if (!m_dmesh)
    {
      m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'pmdtl'.");
      return false;
    }

  if (!rcBuildPolyMeshDetail(m_ctx, *m_pmesh, *m_chf, m_cfg.detailSampleDist, m_cfg.detailSampleMaxError, *m_dmesh))
    {
      m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build detail mesh.");
      return false;
    }

  if (!m_keepInterResults)
    {
      rcFreeCompactHeightfield(m_chf);
      m_chf = 0;
      rcFreeContourSet(m_cset);
      m_cset = 0;
    }

  // At this point the navigation mesh data is ready, you can access it from m_pmesh.
  // See duDebugDrawPolyMesh or dtCreateNavMeshData as examples how to access the data.

  //
  // (Optional) Step 8. Create Detour data from Recast poly mesh.
  //

  // The GUI may allow more max points per polygon than Detour can handle.
  // Only build the detour navmesh if we do not exceed the limit.
  DEBUG("TOTO");
  if (m_cfg.maxVertsPerPoly <= DT_VERTS_PER_POLYGON)
    {
        DEBUG("TITI" << m_pmesh->npolys);
      unsigned char* navData = 0;
      int navDataSize = 0;

      // Update poly flags from areas.
      for (int i = 0; i < m_pmesh->npolys; ++i)
        {
          if (m_pmesh->areas[i] == RC_WALKABLE_AREA)
            {
              m_pmesh->flags[i] = MY_POLYFLAGS_WALK;
              DEBUG("LOL");
            }
        }


      dtNavMeshCreateParams params;
      memset(&params, 0, sizeof (params));
      params.verts = m_pmesh->verts;
      params.vertCount = m_pmesh->nverts;
      params.polys = m_pmesh->polys;
      params.polyAreas = m_pmesh->areas;
      params.polyFlags = m_pmesh->flags;
      params.polyCount = m_pmesh->npolys;
      params.nvp = m_pmesh->nvp;
      params.detailMeshes = m_dmesh->meshes;
      params.detailVerts = m_dmesh->verts;
      params.detailVertsCount = m_dmesh->nverts;
      params.detailTris = m_dmesh->tris;
      params.detailTriCount = m_dmesh->ntris;
      params.offMeshConVerts = m_geom->getOffMeshConnectionVerts();
      params.offMeshConRad = m_geom->getOffMeshConnectionRads();
      params.offMeshConDir = m_geom->getOffMeshConnectionDirs();
      params.offMeshConAreas = m_geom->getOffMeshConnectionAreas();
      params.offMeshConFlags = m_geom->getOffMeshConnectionFlags();
      params.offMeshConUserID = m_geom->getOffMeshConnectionId();
      params.offMeshConCount = m_geom->getOffMeshConnectionCount();
      params.walkableHeight = m_agentHeight;
      params.walkableRadius = m_agentRadius;
      params.walkableClimb = m_agentMaxClimb;
      rcVcopy(params.bmin, m_pmesh->bmin);
      rcVcopy(params.bmax, m_pmesh->bmax);
      params.cs = m_cfg.cs;
      params.ch = m_cfg.ch;
      params.buildBvTree = true;

      if (!dtCreateNavMeshData(&params, &navData, &navDataSize))
        {
          ERROR("Could not build Detour navmesh.");
          return false;
        }

      m_navMesh = dtAllocNavMesh();
      if (!m_navMesh)
        {
          dtFree(navData);
          m_ctx->log(RC_LOG_ERROR, "Could not create Detour navmesh");
          return false;
        }

      dtStatus status;

      status = m_navMesh->init(navData, navDataSize, DT_TILE_FREE_DATA);
      if (dtStatusFailed(status))
        {
          dtFree(navData);
          m_ctx->log(RC_LOG_ERROR, "Could not init Detour navmesh");
          return false;
        }

      status = m_navQuery->init(m_navMesh, 2048);
      if (dtStatusFailed(status))
        {
          m_ctx->log(RC_LOG_ERROR, "Could not init Detour navmesh query");
          return false;
        }
    }

  m_ctx->stopTimer(RC_TIMER_TOTAL);

  // Show performance stats.
  // duLogBuildTimes(*m_ctx, m_ctx->getAccumulatedTime(RC_TIMER_TOTAL));
  INFO("Polimesh: " << m_pmesh->nverts << " vertices, " << m_pmesh->npolys << " polygons.");

  m_totalBuildTimeMs = m_ctx->getAccumulatedTime(RC_TIMER_TOTAL) / 1000.0f;

  return true;
}
