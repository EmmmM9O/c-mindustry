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
template <typename T> class UdpConnection {
private:
  Struct::Socket socket;
  ByteBuffer readBuffer, writeBuffer;
  NetSerializer<T> *serialization;

public:
  UdpConnection(NetSerializer<T> *serialization_, int bufferSize);
  ~UdpConnection();
  void close();
  void connect(int port, std::string ip);
  java::AnyObject<T> readObject();
  void send(java::AnyObject<T> obj);
};
} // namespace net
} // namespace arc