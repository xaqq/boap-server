/* 
 * File:   ByteArray.hpp
 * Author: xaqq
 *
 * Created on October 27, 2013, 2:56 PM
 */

#pragma once
#include <vector>
#include <cstdint>
#include <string>
typedef std::vector<std::uint8_t> ByteArray;

ByteArray &operator<<(ByteArray &ba, const std::string &str);
ByteArray &operator<<(ByteArray &ba, std::uint16_t val);