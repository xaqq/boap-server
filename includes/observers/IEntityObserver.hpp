/* 
 * File:   IEntityObserver.hpp
 * Author: xaqq
 *
 * Created on December 3, 2013, 6:13 PM
 */

#ifndef IENTITYOBSERVER_HPP
#define	IENTITYOBSERVER_HPP

/**
 * Interface to observer an entity.
 * 
 */
class IEntityObserver : public std::enable_shared_from_this<IEntityObserver>
{
public:

  virtual ~IEntityObserver() { }
  
  virtual void speak(std::shared_ptr<class GameEntity> e, const std::string &str)
  {
    onSpeak(e, str);
  }

  virtual void outOfResource(std::shared_ptr<class ResourceEntity> e)
  {
    onOutOfResource(e);
  }

private:
  /**
   * A Resource entity went out of resource.
   * @param e
   */
  virtual void onOutOfResource(std::shared_ptr<ResourceEntity> e) = 0;
  
  virtual void onSpeak(std::shared_ptr<class GameEntity>, const std::string &str)  = 0;

};

#endif	/* IENTITYOBSERVER_HPP */

