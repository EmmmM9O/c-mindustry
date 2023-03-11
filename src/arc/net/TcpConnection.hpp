#include "../../java/nio/ByteBuffer.cpp"
#include "../../struct/Socket.cpp"
#include "./FrameworkMessage.cpp"
#include "./NetSerializer.cpp"
#include <boost/any.hpp>
#include <chrono>
#include <iostream>
namespace arc {
namespace net {
class TcpConnection {
private:
  bool debug = true;
  NetSerializer *serialization;
  Struct::Socket socket;
  java::nio::ByteBuffer readBuffer, writeBuffer;
  int timeout;

public:
  std::string getIP();
  ~TcpConnection();
  short currentObjectLength = 0;
  TcpConnection(NetSerializer *serialization_, int writeBufferSize,
                int objectBufferSize);
  void close();
  void connect(int port, std::string ip, int time);
  boost::any readObject();
  int send(boost::any obj);
};
} // namespace net
} // namespace arc
