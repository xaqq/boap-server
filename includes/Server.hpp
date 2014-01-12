/* 
 * File:   Server.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 6:24 PM
 */

#ifndef SERVER_HPP
#define	SERVER_HPP

#include <atomic>
#include <memory>
#include <list>
#include <thread>
#include <map>
#include "SafeQueue.hpp"
#include "APacket.hpp"
#include "world/World.hpp"
#include "observers/AMainThreadInstanceObserver.hpp"
#include "world/AreaInstance.hpp"

class APacket;
class AClient;
class APacketHandler;

class Server : public AMainThreadInstanceObserver
{
public:

    typedef std::map<std::shared_ptr<AClient>, std::shared_ptr<AreaInstance >> ClientInstanceMap;
    typedef std::map<std::shared_ptr<AreaInstance>, std::shared_ptr<std::thread>> InstanceThreadMap;
    typedef std::list<std::shared_ptr<AClient >> ClientList;
    typedef SafeQueue<std::shared_ptr<APacket >> PacketList;
    typedef std::list<std::shared_ptr<APacketHandler >> PacketHandlerList;

    typedef std::vector<std::shared_ptr<AreaInstance >> InstanceList;


    Server(const Server& orig) = delete;
    virtual ~Server();

    static Server &instance();

    /**
     * Call to shutdown the server;
     */
    void stop();

    /**
     * Server main loop;
     */
    void run();

    /**
     * Asynchronously add the client to the server's client list.
     * This function is thread safe, because it simply queue the call
     * @param c
     */
    void addClient(std::shared_ptr<AClient> c);

    /**
     * Asynchronously remove the client to the server's client list.
     * This function is thread safe, because it simply queue the call
     * @param c
     */
    void removeClient(std::shared_ptr<AClient> c);


    /**
     * This returns the list of client known by the server. This is intended for use by packet handler
     * @return  list of client
     */
    const ClientList &clients() const;

    /**
     * Use to schedule a call of f() in the server's thread.
     * This method is thread safe.
     * @param f
     */
    void post(std::function<void() > f)
    {
        operationQueue_.push(f);
    }

    /**
     * Use to push a packet that will be handled later; 
     * This is thread safe;
     */
    void pushPacket(std::shared_ptr<APacket> p)
    {
        packets_.push(p);
    }

    
    /**
     * A new AreaInstance is ready to run.
     * This method will setup a thread for the instance to run.
     * 
     * The instance will self-initialize itself, in its own thread.
     */
    void registerInstance(std::shared_ptr<AreaInstance> i);
    
    const InstanceList &games() const;

private:
    Server();

    /**
     * Initialize the server, creating required area instance if required, loading up previously saved ones, etc
     * @return 
     */
    bool initialize();
    
    /**
     * Perform some cleanup before returning from run();
     * Currently, it erase all AreaInstance, so each start is a clean, new one.
     */
    void cleanup();

    static Server *instance_;

    std::atomic_bool isRunning_;

    ClientList clients_;
    PacketList packets_;
    PacketHandlerList packetHandlers_;

    /**
     * Invoke queued handler;
     */
    void flush_operations();

    /**
     * Invoke packet handler;
     */
    void handle_packets();

    SafeQueue<std::function<void () >> operationQueue_;


    /**
     * AreaInstance the server is running
     */
    InstanceList instances_;

    /**
     * Map between client and game
     */

    ClientInstanceMap clientInstance_;

    InstanceThreadMap instancesThread_;

    void onInstanceStopped(std::shared_ptr<AreaInstance>, SMSGGameStatus::Status) override;
    void onClientJoined(std::shared_ptr<AreaInstance> game, std::shared_ptr<Client> c) override;
};

#endif	/* SERVER_HPP */

