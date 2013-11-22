/* 
 * File:   Game.cpp
 * Author: xaqq
 * 
 * Created on November 21, 2013, 11:32 PM
 */

#include "world/Game.hpp"
#include "Server.hpp"
#include <thread>
#include "world/World.hpp"
#include "Log.hpp"
#include "Clock.hpp"

Game::Game() :
isRunning_(true),
world_(nullptr){ }

Game::~Game()
{
  delete world_;
  DEBUG("Game Destroyed");
}

bool Game::init()
{
  world_ = new World();
}

void Game::handle_packets()
{
  
  std::shared_ptr<APacket> packet;

  while (packets_.tryPop(packet))
    {
      for (auto & handler : packetHandlers_)
        {
          if (!packet)
            {
              WARN("No Packet !");
            }
          if (!packet->acceptHandler(handler.get()))
            {
              INFO("Handler dropped packet");
              break;
            }
        }
    }
}
void Game::run()
{
  int ticks_per_sec = 1;
  int ms_per_tick = 1000 / ticks_per_sec;

  init();
  while (isRunning_)
    {
      Clock::time_point t;
      t = Clock::now();

      DEBUG("Game " << uuid_() << " is running");
      //world_->update();
      Milliseconds diff = std::chrono::duration_cast<Milliseconds > (Clock::now() - t);

      if (diff.count() > ms_per_tick)
        {
          WARN("Game " << uuid_() << "can't keep up; this tick took " << diff.count() << " instead of maximum " << ms_per_tick);
        }
      else if (diff.count() < ms_per_tick)
        {
          std::this_thread::sleep_for(Milliseconds(ms_per_tick) - diff);
        }
    }
  DEBUG("Game stopped running");
}

const std::string &Game::uuid() const
{
  std::lock_guard<std::mutex> guard(mutex_);
  return uuid_.toString();
}

void Game::stop()
{
  DEBUG("Game " << uuid() << "stop");
  isRunning_ = false;
}

int Game::countPlayers() const
{
  std::lock_guard<std::mutex> guard(mutex_);
  
  int count = 0;
  for (auto &e : entities_)
    {
      if (e->isPlayer())
        count++;
    }
  return count;
}