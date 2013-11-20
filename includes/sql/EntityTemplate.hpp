/* 
 * File:   EntityTemplate.hpp
 * Author: xaqq
 *
 * Created on November 14, 2013, 5:54 AM
 */

#ifndef ENTITYTEMPLATE_HPP
#define	ENTITYTEMPLATE_HPP

#include <memory>
#include <cppconn/connection.h>
#include "sql/SqlHandler.hpp"

class EntityTemplate
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
  std::string scriptName_;
  std::size_t shape_id;
  bool affectNavMesh_;
};

#endif	/* ENTITYTEMPLATE_HPP */

