/* 
 * File:   EntityTemplate.hpp
 * Author: xaqq
 *
 * Created on November 14, 2013, 5:54 AM
 */

#ifndef ENTITYTEMPLATE_HPP
#define	ENTITYTEMPLATE_HPP

#include <memory>

class EntityTemplate
{
public:
  
  static std::shared_ptr<EntityTemplate> loadTemplate(std::size_t id);
  
  std::size_t id_;
  std::string name_;
  std::string scriptName_;
};

#endif	/* ENTITYTEMPLATE_HPP */

