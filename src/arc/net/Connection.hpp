#pragma once

#include "./TcpConnection.cpp"
#include "./UdpConnection.cpp"
#include <boost/any.hpp>
#include <string>
#include <sys/socket.h>

namespace arc {
namespace net {
class Connection;
class NetListener {
public:
  virtual void received(Connection *con, boost::any obj) {}
  virtual void connected(Connection *connection) {}
};
class Connection {
public:
  std::string name;
  TcpConnection tcp;
  UdpConnection udp;
  std::list<NetListener *> listeners;
  volatile bool isConnected;
  int id = -1;
  Connection(NetSerializer *serialization, int writeBufferSize,
             int objectBufferSize);

public:
  std::string getIP();
  int getID();
  bool getIsConnected();
  void sendTCP(boost::any o);

  void sendUDP(boost::any o);

  void close();
  void notifyReceived(boost::any obj);
  void addListener(NetListener *listener);
};
} // namespace net
} // namespace arc
