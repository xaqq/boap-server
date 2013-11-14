/* 
 * File:   Clock.hpp
 * Author: xaqq
 *
 * Created on November 12, 2013, 6:15 PM
 */

#ifndef CLOCK_HPP
#define	CLOCK_HPP
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds Milliseconds;

Milliseconds deltaTime(bool reset = false);
#endif	/* CLOCK_HPP */

