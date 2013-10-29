#include <boost/asio.hpp>


namespace Net
{

  class TcpServer
  {
  public:

    TcpServer(boost::asio::io_service& io_service, short port)
    : acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    socket_(io_service),
    signals_(io_service)
    {
      signals_.add(SIGINT);
      signals_.async_wait(std::bind(&TcpServer::stop, this));
      do_accept();
    }

  private:
    void do_accept();
    void stop();

    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::signal_set signals_;
  };
};
