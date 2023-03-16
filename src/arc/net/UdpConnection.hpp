#pragma once

#include "../../java/nio/ByteBuffer.cpp"
#include "../../struct/net/Socket2.cpp"
#include "./FrameworkMessage.cpp"
#include "./NetSerializer.cpp"
#include <boost/asio/ip/udp.hpp>
#include <regex>
#include <string>
using namespace java::nio;
namespace arc {
namespace net {
template <typename T> class UdpConnection {
private:
  // Struct::Net::TCPSocket socket;
  ByteBuffer readBuffer, writeBuffer;
  NetSerializer<T> *serialization;

public:
  UdpConnection(NetSerializer<T> *serialization_, int bufferSize,
                boost::asio::ip::udp::socket *soc,
                boost::asio::ip::udp::resolver *re);
  ~UdpConnection();
  void close();
  void connect(int port, std::string ip);
  java::AnyTwo<java::AnyObject<T>,
               java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
  readObject();
  void send(java::AnyTwo<java::AnyObject<T>,
                         java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
                obj);
};
} // namespace net
} // namespace arc