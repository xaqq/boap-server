#include "exceptions/WorldFailedInit.hpp"

WorldFailedInit::WorldFailedInit(const std::string& reason) noexcept : std::runtime_error(reason)
{
  reason_ = "The world failed to initialize: " + reason;
}

WorldFailedInit::WorldFailedInit(const WorldFailedInit& o) noexcept: std::runtime_error(o.reason_)
{
  reason_ = o.reason_;
}


const char* WorldFailedInit::what() const noexcept
{
  return reason_.c_str();
}