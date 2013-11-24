/* 
 * File:   WorldFailedInit.hpp
 * Author: xaqq
 *
 * Created on November 23, 2013, 7:48 PM
 */

#ifndef WORLDFAILEDINIT_HPP
#define	WORLDFAILEDINIT_HPP

#include <stdexcept>
#include <string>

class WorldFailedInit : public std::runtime_error
{
  public:
    WorldFailedInit(const std::string &reason) noexcept;
    WorldFailedInit(const WorldFailedInit &o) noexcept;
    WorldFailedInit &operator=(const WorldFailedInit &) noexcept;
    virtual ~WorldFailedInit() noexcept {};
    virtual const char* what() const noexcept;
    
    private:
      std::string reason_;
};


#endif	/* WORLDFAILEDINIT_HPP */

