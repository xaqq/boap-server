#include <string.h>
#include <ctype.h>
#include "Log.hpp"
#include "ByteArray.hpp"

ByteArray &operator<<(ByteArray &ba, const std::string &str)
{
  auto size = ba.size();
  ba.resize(size + str.length());
  memcpy(&ba[size], str.c_str(), str.length());
  return ba;
}

ByteArray &operator<<(ByteArray &ba, std::uint16_t val)
{
  auto size = ba.size();
  ba.resize(size + 2);
  memcpy(&ba[size], &val, 2);
  return ba;
}
