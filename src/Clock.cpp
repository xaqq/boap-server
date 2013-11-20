#include "Log.hpp"
#include "Clock.hpp"

Milliseconds deltaTime(bool reset)
{
  static Clock::time_point prev;

  if (reset)
    {
      prev = Clock::now();
    }
  return std::chrono::duration_cast<Milliseconds > (Clock::now() - prev);
}
