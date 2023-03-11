#include "./TcpConnection.hpp"

std::string arc::net::TcpConnection::getIP() { return socket.Chost; }
arc::net::TcpConnection::~TcpConnection() { close(); }
short currentObjectLength = 0;
arc::net::TcpConnection::TcpConnection(NetSerializer *serialization_,
                                       int writeBufferSize,
                                       int objectBufferSize)
    : socket(Struct::domain::IPV4, Struct::type::TCP, 0) {
  serialization = serialization_;
  readBuffer = java::nio::ByteBuffer::allocate(objectBufferSize);
  writeBuffer = java::nio::ByteBuffer::allocate(writeBufferSize);
  readBuffer.flip();
}
void arc::net::TcpConnection::close() {
  if (socket.connectd)
    socket.close();
}
void arc::net::TcpConnection::connect(int port, std::string ip, int time) {
  timeout = time;
  if (socket.connectd)
    close();
  currentObjectLength = 0;
  writeBuffer.clear();
  readBuffer.clear();
  readBuffer.flip();
  socket.connect(port, ip);
}
boost::any arc::net::TcpConnection::readObject() {
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
    return nullptr;
  }
}
int arc::net::TcpConnection::send(boost::any obj) {
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
