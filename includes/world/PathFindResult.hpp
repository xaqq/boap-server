/* 
 * File:   PathFindResult.hpp
 * Author: xaqq
 *
 * Created on December 4, 2013, 4:34 PM
 */

#ifndef PATHFINDRESULT_HPP
#define	PATHFINDRESULT_HPP

#include <vector>

/**
 * This class encapsulate the underlying path finding result and provide an easy
 * way for entity to do path planning
 */
class PathFindResult
{
public:

  /**
   * Since this is tightly coupled with the PathFindHelper, we declare it friend.
   * This reinforce encapsulation because we can expose a ready-only API.
   */
  friend class PathFindHelper;

  /**
   * This is an enum for the status of the path find query
   */
  enum class Status
  {
    NO_START, /*!< Cannot find the start polygone; The start point is too far from a navmesh polygone */
    NO_END, /*!< Cannot find the end polygone; The end point is too far from a navmesh polygone */
    VALID, /*!< A valid path has been found */
    TOO_LONG, /*!< Path is too long ; That means the result objet will not contain the full path */
    NO_PATH, /*!< Their is no way to go from start to end */
    UNKOWN /*!< Default value set a construction */
  };
  PathFindResult();
  PathFindResult(const PathFindResult& orig);
  virtual ~PathFindResult();

  /**
   * This is a getter for the object's status.
   * @return The status of the result.
   */
  Status status() const;

  /**
   * Accessor to corners.
   * 
   * @return the corners of the path
   */
  const std::vector<btVector3> &corners() const;

  /**
   * Calculate the length of the path.
   * 
   * Note that if the path status is TOO_LONG, this will return the length of the path that
   * this results holds (ie an incomplete one).
   * That means that the real total path length will be more than the  returned value.
   * 
   * @return length of the path
   */
  float length() const;
  
  /**
   * Check wether or not the path is usable. this is based on the status.
   * A usable path has at least one corner
   */
  bool isUsable() const;

  /**
   * Returns the next corner in the path
   */
  const btVector3 &nextCorner() const;
  
private:
  /**
   * This holds the status of the path.
   */
  Status status_;

  /**
   * This stores the corners (passage points) of the path
   */
  std::vector<btVector3> corners_;

  /**
   * Starting point (on the navmesh) , in world coordinate.
   */
  btVector3 start_;
};

#endif	/* PATHFINDRESULT_HPP */

