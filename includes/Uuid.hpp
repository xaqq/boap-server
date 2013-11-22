/* 
 * File:   Uuid.hpp
 * Author: xaqq
 *
 * Created on November 21, 2013, 10:46 PM
 */

#ifndef UUID_HPP
#define	UUID_HPP

#include <string>
#include <mutex>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

/**
 * Wrapper around boost uuid
 */
class Uuid
{
public:
  Uuid();
  Uuid(const Uuid& orig);
  virtual ~Uuid();

  bool operator==(const Uuid &o);

  /**
   * Return the boost uuid object
   */
  boost::uuids::uuid &operator()();

  const boost::uuids::uuid & operator()()const;

  const std::string &toString() const;

private:
  /**
   * Textual representation; set once in the constructor;
   */
  std::string text_;

  /**
   * Static mutex because boost::mt19937 may not be thread safe;
   */
  static std::mutex mutex_;

  boost::uuids::uuid uuid_;

  /**
   * Random engine used by the generator
   */
  static boost::mt19937 random_;

  /**
   * Has the global generator be seed or not
   */
  static bool seeded_;

};

#endif	/* UUID_HPP */

