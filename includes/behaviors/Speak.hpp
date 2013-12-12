/* 
 * File:   Speak.hpp
 * Author: xaqq
 *
 * Created on December 11, 2013, 7:54 PM
 */

#ifndef SPEAK_HPP
#define	SPEAK_HPP

#include "BehaviorTree.h"

namespace Behaviors
{
class Speak : public BehaviorTree::BehaviorTreeNode
{
public:
  Speak(const std::string &str);
  Speak(const Speak& orig) = delete;;
  virtual ~Speak();
  
  virtual BehaviorTree::BEHAVIOR_STATUS execute(void *agent) override;
  virtual void init(void *agent) override;
private:
  std::string str_;
};
}
#endif	/* SPEAK_HPP */

