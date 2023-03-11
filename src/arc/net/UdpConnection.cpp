#include "./UdpConnection.hpp"
using namespace java::nio;

arc::net::UdpConnection::UdpConnection(NetSerializer *serialization_,
                                       int bufferSize)
    : socket(Struct::domain::IPV4, Struct::type::UDP, 0) {
  serialization = serialization_;
  readBuffer = ByteBuffer::allocate(bufferSize);
  writeBuffer = ByteBuffer::allocate(bufferSize);
}
arc::net::UdpConnection::~UdpConnection() { close(); }
void arc::net::UdpConnection::close() {
  if (socket.connectd) {
    socket.close();
  }
}
void arc::net::UdpConnection::connect(int port, std::string ip) {
  close();
  readBuffer.clear();
  writeBuffer.clear();
  if (!socket.connectd) {
    socket.connect(port, ip);
  }
}
boost::any arc::net::UdpConnection::readObject() {
  readBuffer.flip();
  auto o = serialization->read(readBuffer);
  readBuffer.clear();
  return o;
}

template <typename T> void arc::net::UdpConnection::send(T obj) {
  if (socket.connectd) {
    writeBuffer.clear();
    serialization->write(writeBuffer, obj);
    writeBuffer.flip();
    socket.send(writeBuffer.byteStream.data(), writeBuffer.byteStream.size());
  }
}