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
#include "handlers/JoinGameHandler.hpp"

Game::Game(const std::string &scene) :
sceneName_(scene),
isRunning_(true),
world_(nullptr) { }

Game::~Game()
{
  DEBUG("Game Destroyed");
}

bool Game::init()
{
  world_ = std::make_shared<World>(sceneName_);
  packetHandlers_.push_back(std::shared_ptr<APacketHandler > (new JoinGameHandler()));
  return true;
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
  int ticks_per_sec = 20;
  int ms_per_tick = 1000 / ticks_per_sec;

  init();
  try
    {
      while (isRunning_)
        {
          Clock::time_point t;
          t = Clock::now();

          handle_packets();
          world_->update();
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
  catch (std::exception &e)
    {
      ERROR("An exception occured in game " << uuid() << ": " << e.what());
    }

  dispatch(std::bind(&IGameObserver::gameStopped, std::placeholders::_1, shared_from_this(), SMSGGameStatus::FAILED_INIT));
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

bool Game::joinGame(std::shared_ptr<Client> client)
{
  playersToEntities_[client] = world_->spawn(2);
  if (playersToEntities_[client])
    return true;
  return false;
}