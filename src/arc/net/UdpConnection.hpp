#pragma once

#include "../../java/nio/ByteBuffer.cpp"
#include "../../struct/Socket.cpp"
#include "./FrameworkMessage.cpp"
#include "./NetSerializer.cpp"
#include <regex>
#include <string>
using namespace java::nio;
namespace arc {
namespace net {
class UdpConnection {
private:
  Struct::Socket socket;
  ByteBuffer readBuffer, writeBuffer;
  NetSerializer *serialization;

public:
  UdpConnection(NetSerializer *serialization_, int bufferSize);
  ~UdpConnection();
  void close();
  void connect(int port, std::string ip);
  boost::any readObject();
  template <typename T> void send(T obj);
};
} // namespace net
} // namespace arc