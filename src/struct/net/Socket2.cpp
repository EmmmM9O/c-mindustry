#include "Socket2.hpp"
#include <boost/asio/buffer.hpp>
#include <string>

Struct::Net::TCPSocket::TCPSocket(boost::asio::io_service *io) {
  sock = new boost::asio::ip::tcp::socket(*io);
  resolver = new boost::asio::ip::tcp::resolver(*io);
}
boost::asio::ip::tcp::resolver::query
Struct::Net::TCPSocket::query(std::string host, int address) {
  return boost::asio::ip::tcp::resolver::query(host, std::to_string(address));
}
void Struct::Net::TCPSocket::read() {
  sock->async_read_some(boost::asio::buffer(readBuffer),
                        boost::bind(read_handler, _2, this));
}
void Struct::Net::TCPSocket::connect(
    boost::asio::ip::tcp::resolver::query query) {
  resolver->async_resolve(
      query,
      [this](const boost::system::error_code &ec,
             boost::asio::ip::tcp::resolver::iterator it) -> void {
        if (!ec) {
          sock->async_connect(
              *it, [this](const boost::system::error_code &ec) -> void {
                if (!ec) {
                  connected = true;
                  sock->async_read_some(boost::asio::buffer(readBuffer),
                                        boost::bind(read_handler, _2, this));
                } else {
                  throw ec;
                }
              });
        } else {
          throw ec;
        }
      });
}
void Struct::Net::TCPSocket::close() {
  sock->close();
  connected = false;
}
Struct::Net::TCPSocket::TCPSocket(boost::asio::ip::tcp::resolver *re,
                                  boost::asio::ip::tcp::socket *soc) {
  sock = soc;
  resolver = re;
}
void Struct::Net::TCPSocket::connect(std::string host, int port) {
  connect(query(host, port));
}
void Struct::Net::TCPSocket::send(std::string arg) { sock->send(arg); }
void Struct::Net::TCPSocket::send(unsigned char arg[], int size) {
  std::string a;
  for (int i = 0; i < size; i++)
    a.push_back(arg[i]);
  sock->send(a);
}