#include <boost/asio.hpp>
#include "net/TcpServer.hpp"

int main(int argc, char* argv[])
{
  try
    {
      boost::asio::io_service io_service;
      Net::TcpServer server(io_service, 4242);
      io_service.run();
    }
  catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << "\n";
    }

  return 0;
}
