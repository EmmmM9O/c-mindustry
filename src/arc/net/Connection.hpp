#pragma once

#include "./TcpConnection.cpp"
#include "./UdpConnection.cpp"
#include <boost/any.hpp>
#include <string>
#include <sys/socket.h>

namespace arc {
namespace net {
template <typename T> class Connection;
template <typename T> class NetListener {
public:
  virtual void received(
      Connection<T> *con,
      java::AnyTwo<java::AnyObject<T>,
                   java::AnyObject<FrameworkMessage::_FrameworkMessage_>>) {}
  virtual void connected(Connection<T> *connection) {}
};
template <typename T> class Connection {
public:
  std::string name;
  TcpConnection<T> tcp;
  UdpConnection<T> udp;
  std::list<NetListener<T> *> listeners;
  volatile bool isConnected;
  int id = -1;
  Connection(NetSerializer<T> *serialization, int writeBufferSize,
             int objectBufferSize);
  std::string getIP();
  int getID();
  bool getIsConnected();
  void
  sendTCP(java::AnyTwo<java::AnyObject<T>,
                       java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
              o);
  void
  sendUDP(java::AnyTwo<java::AnyObject<T>,
                       java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
              o);
  void close();
  void notifyReceived(
      java::AnyTwo<java::AnyObject<T>,
                   java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
          obj);
  void addListener(NetListener<T> *listener);
};
} // namespace net
} // namespace arc
