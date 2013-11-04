/* 
 * File:   UdpProtocolHandler.cpp
 * Author: xaqq
 * 
 * Created on October 30, 2013, 1:33 AM
 */

#include <boost/asio.hpp>
#include "UdpProtocolHandler.hpp"
#include "Log.hpp"
#include "Scheduler.hpp"
#include <thread>
using namespace Net;

UdpProtocolHandler::UdpProtocolHandler(UdpServer &s, boost::asio::ip::udp::endpoint e) :
AUdpProtocolHandler(s, e) { }

UdpProtocolHandler::~UdpProtocolHandler()
{
  INFO("UDPProtocolhandler destroyed");
}

void UdpProtocolHandler::bytesAvailable(ByteArray && bytes)
{
  INFO("This thread: " << std::this_thread::get_id());
  Scheduler::instance()->runInServerThread(std::bind([](int a) { INFO ("Lambda running in thread (" << a << ") " << std::this_thread::get_id()); }, 42));
  INFO("Packet from " << endpoint().address().to_string() << ":" << endpoint().port() << ";");

}