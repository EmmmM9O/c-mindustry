#include "./TcpConnection.hpp"
template <typename T> std::string arc::net::TcpConnection<T>::getIP() {
  return socket.Chost;
}
template <typename T> arc::net::TcpConnection<T>::~TcpConnection() { close(); }
short currentObjectLength = 0;
template <typename T>
arc::net::TcpConnection<T>::TcpConnection(NetSerializer<T> *serialization_,
                                          int writeBufferSize,
                                          int objectBufferSize)
    : socket(Struct::domain::IPV4, Struct::type::TCP, 0) {
  serialization = serialization_;
  readBuffer = java::nio::ByteBuffer::allocate(objectBufferSize);
  writeBuffer = java::nio::ByteBuffer::allocate(writeBufferSize);
  readBuffer.flip();
}
template <typename T> void arc::net::TcpConnection<T>::close() {
  if (socket.connectd)
    socket.close();
}
template <typename T>
void arc::net::TcpConnection<T>::connect(int port, std::string ip, int time) {
  timeout = time;
  if (socket.connectd)
    close();
  currentObjectLength = 0;
  writeBuffer.clear();
  readBuffer.clear();
  readBuffer.flip();
  socket.connect(port, ip);
}
template <typename T>
java::AnyTwo<java::AnyObject<T>,
             java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>>
arc::net::TcpConnection<T>::readObject() {
  if (socket.connectd) {
    if (currentObjectLength == 0) {
      // currentObjectLength=readBuffer.ReadShort();
      int lengthLength = serialization->getLengthLength();
      currentObjectLength = serialization->readLength(readBuffer);
      if (readBuffer.remaining() < lengthLength) {
        std::cout << "Read new Buffer" << std::endl;
        try {
          socket.read(readBuffer, timeout);
        } catch (Struct::TimeOut &e) {
          throw e;
        }
      }
    }
    auto b = readBuffer.streamIter;
    int length = currentObjectLength;
    currentObjectLength = 0;
    readBuffer.streamIter = b;
    return serialization->read(readBuffer);
  } else {
    return java::AnyTwo<java::AnyObject<T>,java::AnyObject<FrameworkMessage::_FrameworkMessage_>>();
  }
}
template <typename T>
int arc::net::TcpConnection<T>::send(
    java::AnyTwo<java::AnyObject<T>,
                 java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
        obj) {
  int lengthLength = serialization->getLengthLength();
  int start = writeBuffer.streamIter;
  writeBuffer.streamIter += lengthLength;
  serialization->write(writeBuffer, obj);
  int end = writeBuffer.streamIter;
  writeBuffer.streamIter = start;
  serialization->writeLength(writeBuffer, end - lengthLength - start);
  serialization->writeLength(writeBuffer, end - lengthLength - start);
  writeBuffer.streamIter = end;
  socket.send(writeBuffer.byteStream.data(), writeBuffer.byteStream.size());
  return end - start;
}
