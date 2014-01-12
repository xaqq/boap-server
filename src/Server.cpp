/* 
 * File:   Server.cpp
 * Author: xaqq
 * 
 * Created on October 29, 2013, 6:24 PM
 */

#include <unistd.h>
#include <thread>
#include "Server.hpp"
#include "Log.hpp"
#include "AClient.hpp"
#include "Clock.hpp"
#include "BoapFactory.hpp"
#include "Scheduler.hpp"
#include "APacket.hpp"
#include "Client.hpp"
#include "world/Game.hpp"
#include "db/DBManager.hpp"
#include "odb/session.hxx"
#include "db/DAO.hpp"

Server *Server::instance_ = nullptr;

Server &Server::instance()
{
    if (!instance_)
        instance_ = new Server();
    return *instance_;
}

Server::Server() : isRunning_(true),
packetHandlers_(BoapFactory::createPacketHandlers())
{
}

Server::~Server()
{
}

void Server::flush_operations()
{
    std::function<void () > f;
    std::size_t size = operationQueue_.size();
    std::size_t i = 0;

    while (i++ < size && operationQueue_.tryPop(f))
    {
        f();
    }
}

void Server::handle_packets()
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

void lol()
{
    DB::DatabasePtr db = DB::DBManager::instance().db();
    using namespace DB;
    odb::transaction t(db->begin());

    Geometry3dBox box3d;
    box3d.description("A 3x3x3 cube with its center in (0, 0, 0)");
    box3d.halfExtends({1.5, 1.5, 1.5});

    std::shared_ptr<DB::Geometry2dBox> box2d(new DB::Geometry2dBox());
    box2d->description("A 2d box, on the floor, 10x7.");
    box2d->halfExtends({5, 3.5});
    box2d->angles({90, 0, 0});

    Geometry3dBox simpleHitBox;
    simpleHitBox.description("A simple 0.5 x 1 x 0.5 box, relative Y value of 0.5 to be on the floor");
    simpleHitBox.halfExtends({0.25, 0.5, 0.25});
    simpleHitBox.relativeDistance({0, 0.5, 0});

    GeometrySphere sphere;
    sphere.relativeDistance({0, 1, 0});
    sphere.description("A sphere with radius = 1, with a relative Y value of 1 so that it should touch the floor");
    sphere.radius(1);

    db->persist<GeometryObject>(box3d);
    db->persist<GeometryObject>(simpleHitBox);
    db->persist<DB::GeometryObject>(box2d);
    db->persist<GeometryObject>(sphere);
    t.commit();
}

bool Server::initialize()
{
    auto areas = DB::DAO::findAll<DB::Area>();
    for (auto area : areas)
    {
        INFO("Area: id(" << area->id() << "), name(" << area->name() << ")");
        std::shared_ptr<AreaInstance> areaInstance(new AreaInstance(area));
        registerInstance(areaInstance);

        std::this_thread::sleep_for(Milliseconds(3000));
        areaInstance->stop();
    }
    return true;
}

void Server::run()
{
    int ticks_per_sec = 100;
    int ms_per_tick = 1000 / ticks_per_sec;
    //
    //        lol();
    //        return;

    if (!initialize())
    {
        throw std::runtime_error("Cannot initialize server");
    }
    //  addGame(std::shared_ptr<Game>(new Game("Test Level")));
    while (isRunning_)
    {
        Clock::time_point t;
        t = Clock::now();

        // INFO("Server is running. Stats: " << clients_.size() << " clients.");
        flush_operations();
        handle_packets();
        Milliseconds diff = std::chrono::duration_cast<Milliseconds > (Clock::now() - t);

        if (diff.count() > ms_per_tick)
        {
            WARN("Server can't keep up; this tick took " << diff.count() << " instead of maximum " << ms_per_tick);
        }
        else if (diff.count() < ms_per_tick)
        {
            std::this_thread::sleep_for(Milliseconds(ms_per_tick) - diff);
        }
    }

    for (InstanceThreadMap::iterator it = instancesThread_.begin();
            it != instancesThread_.end();
            ++it)
    {
        it->first->stop();
        // while (1)std::this_thread::sleep_for(Milliseconds(10000));
        //   DEBUG("TITI");
        if (it->second)
            it->second->join(); // thread
    }
    DEBUG("TOTO");
    //   for (auto & gameThread : instancesThread_)
    // {
    //   gameThread.first->stop(); // game
    // gameThread.second.join(); // thread
    //    }

    cleanup();
}

void Server::cleanup()
{
    for (auto areaInstance : instances_)
    {
        if (!areaInstance->erase())
        {
            WARN("Cannot erase areaInstance: " << areaInstance->uuid()());
        }
    }
}

void Server::addClient(std::shared_ptr<AClient> c)
{
    INFO("scheduling client add to server;");

    Scheduler::instance()->runInServerThread(std::bind(
            static_cast<void (ClientList::*)(const std::shared_ptr<AClient> &)> (&ClientList::push_back)
            , &clients_, c));
}

void Server::removeClient(std::shared_ptr<AClient> c)
{
    INFO("scheduling client removal from server;");

    Scheduler::instance()->runInServerThread(std::bind(&ClientList::remove
            , &clients_, c));
}

void Server::stop()
{
    INFO("Stopping server");
    isRunning_ = false;
}

const Server::ClientList &Server::clients() const
{
    return clients_;
}

void Server::registerInstance(std::shared_ptr<AreaInstance> i)
{
    i->registerObserver(shared_from_this());
    instances_.push_back(i);
    instancesThread_[i] = std::make_shared<std::thread>([i]()
    {
        while (i->update());
        DEBUG("Done in game thread");
        //        i->run();
    });
    DEBUG("Instance registered");
}

const Server::InstanceList &Server::games() const
{
    return instances_;
}

void Server::onInstanceStopped(std::shared_ptr<AreaInstance> game, SMSGGameStatus::Status st)
{
    DEBUG("Game with uuid" << game->uuid().toString() << " stopped with status: " << st << "(from thread: " << std::this_thread::get_id());
    instances_.erase(std::find(instances_.begin(), instances_.end(), game));
    instancesThread_[game]->join();
    instancesThread_.erase(game);
}

void Server::onClientJoined(std::shared_ptr<AreaInstance> game, std::shared_ptr<Client> c)
{
    clientInstance_[std::dynamic_pointer_cast<AClient>(c)] = game;
}