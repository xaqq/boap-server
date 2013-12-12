/* 
 * File:   Speak.cpp
 * Author: xaqq
 * 
 * Created on December 11, 2013, 7:54 PM
 */

#include "behaviors/Speak.hpp"
#include "world/GameEntity.hpp"
#include "Log.hpp"

using namespace Behaviors;

Speak::Speak(const std::string &str) : str_(str) { }

Speak::~Speak() { }

BehaviorTree::BEHAVIOR_STATUS Speak::execute(void *agent)
{
  DEBUG("Speaking ...:" << str_);
  GameEntity *e;
  e = reinterpret_cast<GameEntity *>(agent);
  return BehaviorTree::BT_SUCCESS;;
}

void Speak::init(void *agent)
{
  DEBUG("INIT BEHAVIOR SPEAK");
}