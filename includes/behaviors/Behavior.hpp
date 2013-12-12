/* 
 * File:   Behavior.hpp
 * Author: xaqq
 *
 * Created on December 11, 2013, 7:38 PM
 */

#ifndef BEHAVIOR_HPP
#define	BEHAVIOR_HPP

namespace BehaviorTree
{
  class ParallelNode;
}
class Behavior
{
public:
  Behavior();
  Behavior(const Behavior& orig) =delete;
  virtual ~Behavior();

  void update(class GameEntity *e);
  
private:
  BehaviorTree::ParallelNode *brain_;
};

#endif	/* BEHAVIOR_HPP */

