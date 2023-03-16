#include "../../java/nio/ByteBuffer.cpp"
#include "../../struct/net/Socket2.cpp"
#include "../util/Log.cpp"
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
  Struct::Net::TCPSocket socket;
  java::nio::ByteBuffer readBuffer, writeBuffer;
  // boost::asio::ip::tcp::socket *sock;
public:
  std::string getIP();
  ~TcpConnection();
  short currentObjectLength = 0;
  TcpConnection(NetSerializer<T> *serialization_, int writeBufferSize,
                int objectBufferSize, boost::asio::ip::tcp::socket *soc,
                boost::asio::ip::tcp::resolver *re);
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
