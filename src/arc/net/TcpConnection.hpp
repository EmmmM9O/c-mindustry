#include "../../java/nio/ByteBuffer.cpp"
#include "../../struct/Socket.cpp"
#include "./FrameworkMessage.cpp"
#include "./NetSerializer.cpp"
#include <boost/any.hpp>
#include <chrono>
#include <iostream>
namespace arc {
namespace net {
template <typename T> class TcpConnection {
private:
  bool debug = true;
  NetSerializer<T> *serialization;
  Struct::Socket socket;
  java::nio::ByteBuffer readBuffer, writeBuffer;
  int timeout;

public:
  std::string getIP();
  ~TcpConnection();
  short currentObjectLength = 0;
  TcpConnection(NetSerializer<T> *serialization_, int writeBufferSize,
                int objectBufferSize);
  void close();
  void connect(int port, std::string ip, int time);
  java::AnyTwo<java::AnyObject<T>,
               java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
  readObject();
  int send(java::AnyTwo<java::AnyObject<T>,
                        java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
               obj);
};
} // namespace net
} // namespace arc
