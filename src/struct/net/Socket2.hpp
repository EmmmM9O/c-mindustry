
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/function/function_fwd.hpp>
#include <string>
namespace Struct {
namespace Net {
class TCPSocket {
public:
  boost::array<char, 4096> readBuffer;
  // boost::asio::io_service *io_service;
  boost::asio::ip::tcp::resolver *resolver;
  boost::asio::ip::tcp::socket *sock;
  TCPSocket(boost::asio::ip::tcp::resolver *re,
            boost::asio::ip::tcp::socket *soc);
  TCPSocket(boost::asio::io_service *io);
  boost::asio::ip::tcp::resolver::query query(std::string host, int address);
  void connect(boost::asio::ip::tcp::resolver::query query);
  void connect(std::string host, int address);
  boost::function<void(const boost::system::error_code, std::size_t,
                       TCPSocket *sock)>
      read_handler;
  bool connected;
  void close();
  void send(std::string arg);
  void send(unsigned char arr[], int size);
  void read();
};
class UDPSocket {
public:
  boost::array<char, 4096> readBuffer;
  boost::asio::ip::udp::resolver *resolver;
  boost::asio::ip::udp::socket *sock;
  UDPSocket(boost::asio::ip::udp::resolver *re,
            boost::asio::ip::udp::socket *soc);
  boost::asio::ip::udp::resolver::query query(std::string host, int address);
  void connect(std::string host, int address);
  void connect(boost::asio::ip::udp::resolver::query query);
  boost::function<void(const boost::system::error_code, std::size_t,
                       UDPSocket *sock)>
      read_handler;
  bool connected;
  void close();
  void send(std::string arg);
  void send(unsigned char arr[], int size);
  void read();
};
} // namespace Net
} // namespace Struct