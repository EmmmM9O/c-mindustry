#include "./TcpConnection.hpp"
#include <algorithm>
template <typename T> std::string arc::net::TcpConnection<T>::getIP() {
  return "";
}
template <typename T> arc::net::TcpConnection<T>::~TcpConnection() { close(); }
short currentObjectLength = 0;
template <typename T>
arc::net::TcpConnection<T>::TcpConnection(NetSerializer<T> *serialization_,
                                          int writeBufferSize,
                                          int objectBufferSize,
                                          boost::asio::ip::tcp::socket *soc,
                                          boost::asio::ip::tcp::resolver *re)
    : socket(re, soc) {
  socket.read_handler = [this](const boost::system::error_code &ec,
                               std::size_t bytes_transferred,
                               Struct::Net::TCPSocket *sock) -> void {
    for (int i = 0; i < bytes_transferred; i++) {
      readBuffer.byteStream.push_back(sock->readBuffer[i]);
    }
    sock->read();
  };
  serialization = serialization_;
  readBuffer = java::nio::ByteBuffer::allocate(objectBufferSize);
  writeBuffer = java::nio::ByteBuffer::allocate(writeBufferSize);
  readBuffer.flip();
}
template <typename T> void arc::net::TcpConnection<T>::close() {
  if (socket.connected)
    socket.close();
}
template <typename T>
void arc::net::TcpConnection<T>::connect(int port, std::string ip, int time) {
  if (socket.connected)
    close();
  currentObjectLength = 0;
  writeBuffer.clear();
  readBuffer.clear();
  readBuffer.flip();
  socket.connect(ip, port);
}
template <typename T>
java::AnyTwo<java::AnyObject<T>,
             java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>>
arc::net::TcpConnection<T>::readObject() {
  if (socket.connected) {
    if (currentObjectLength == 0) {
      currentObjectLength = readBuffer.ReadShort();
      int lengthLength = serialization->getLengthLength();
      // currentObjectLength = serialization->readLength(readBuffer);
      if (readBuffer.remaining() < lengthLength) {
        // std::cout << "Read new Buffer" << std::endl;
        return java::AnyTwo<
            java::AnyObject<T>,
            java::AnyObject<FrameworkMessage::_FrameworkMessage_>>();
      }
    }
    auto b = readBuffer.streamIter;
    int length = currentObjectLength;
    readBuffer.position(std::min(length + 2, 2));
    std::cout << "Read Pos:" << readBuffer.position() << "for"
              << (int)readBuffer.byteStream[readBuffer.position()] << std::endl;
    currentObjectLength = 0;

    auto obj = serialization->read(&readBuffer);
    readBuffer.since(readBuffer.position());
    return obj;
  } else {
    return java::AnyTwo<
        java::AnyObject<T>,
        java::AnyObject<FrameworkMessage::_FrameworkMessage_>>();
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
