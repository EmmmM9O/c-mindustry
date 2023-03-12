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
  virtual void received(Connection<T> *con, java::AnyObject<T>) {}
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
  void sendTCP(java::AnyObject<T> o);
  void sendUDP(java::AnyObject<T> o);
  void close();
  void notifyReceived(java::AnyObject<T> obj);
  void addListener(NetListener<T> *listener);
};
} // namespace net
} // namespace arc
