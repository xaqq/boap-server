/* 
 * File:   ShapeTemplate.hpp
 * Author: xaqq
 *
 * Created on November 14, 2013, 5:54 AM
 */

#pragma once

#include <memory>
#include <cppconn/connection.h>
#include "sql/SqlHandler.hpp"

class ShapeTemplate
{
public:
  
  static SqlTaskReturnType loadTemplate(sql::Connection *c, std::size_t id);
  
  /**
   * 
   * @return a sql task sql: custom data is a std::list<EntityTemplate>
   */
  static SqlTaskReturnType loadAllTemplate(sql::Connection *c);
  
  std::size_t id_;
  std::string name_;
  btVector3 params_;
};

