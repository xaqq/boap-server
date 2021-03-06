/* 
 * File:   Uuid.cpp
 * Author: xaqq
 * 
 * Created on November 21, 2013, 10:46 PM
 */

#include <sstream>
#include "Uuid.hpp"
#include "Clock.hpp"

boost::mt19937 Uuid::random_;
bool Uuid::seeded_ = false;
std::mutex Uuid::mutex_;

Uuid::Uuid()
{
  std::lock_guard<std::mutex> lock(mutex_);
  std::stringstream ss;

  if (!seeded_)
    {
      random_.seed();
      seeded_ = true;
    }
  boost::uuids::basic_random_generator<boost::mt19937> gen(&random_);
  uuid_ = gen();

  ss << uuid_;
  text_ = ss.str();
}

Uuid::Uuid(const Uuid& orig)
{
  uuid_ = orig.uuid_;
}

Uuid::~Uuid() { }

bool Uuid::operator==(const Uuid &o)
{
  return uuid_ == o.uuid_;
}

boost::uuids::uuid &Uuid::operator()()
{
  return uuid_;
}

const boost::uuids::uuid &Uuid::operator()() const
{
  return uuid_;
}

const std::string &Uuid::toString() const
{
  return text_;
}