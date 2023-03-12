#include "./UdpConnection.hpp"
using namespace java::nio;
template <typename T>
arc::net::UdpConnection<T>::UdpConnection(NetSerializer<T> *serialization_,
                                          int bufferSize)
    : socket(Struct::domain::IPV4, Struct::type::UDP, 0) {
  serialization = serialization_;
  readBuffer = ByteBuffer::allocate(bufferSize);
  writeBuffer = ByteBuffer::allocate(bufferSize);
}
template <typename T> arc::net::UdpConnection<T>::~UdpConnection() { close(); }
template <typename T> void arc::net::UdpConnection<T>::close() {
  if (socket.connectd) {
    socket.close();
  }
}
template <typename T>
void arc::net::UdpConnection<T>::connect(int port, std::string ip) {
  close();
  readBuffer.clear();
  writeBuffer.clear();
  if (!socket.connectd) {
    socket.connect(port, ip);
  }
}
template <typename T>
java::AnyObject<T> arc::net::UdpConnection<T>::readObject() {
  readBuffer.flip();
  auto o = serialization->read(readBuffer);
  readBuffer.clear();
  return o;
}

template <typename T>
void arc::net::UdpConnection<T>::send(java::AnyObject<T> obj) {
  if (socket.connectd) {
    writeBuffer.clear();
    serialization->write(writeBuffer, obj);
    writeBuffer.flip();
    socket.send(writeBuffer.byteStream.data(), writeBuffer.byteStream.size());
  }
}