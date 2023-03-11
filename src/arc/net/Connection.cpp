#pragma once

#include "./Connection.hpp"

arc::net::Connection::Connection(NetSerializer *serialization,
                                 int writeBufferSize, int objectBufferSize)
    : tcp(serialization, writeBufferSize, objectBufferSize),
      udp(serialization, writeBufferSize) {}

std::string arc::net::Connection::getIP() { return tcp.getIP(); }
int arc::net::Connection::getID() { return id; }
bool arc::net::Connection::getIsConnected() { return isConnected; }
void arc::net::Connection::sendTCP(boost::any o) { tcp.send(o); }

void arc::net::Connection::sendUDP(boost::any o) { udp.send(o); }

void arc::net::Connection::close() {
  isConnected = false;
  tcp.close();
  udp.close();
}
void arc::net::Connection::notifyReceived(boost::any obj) {
  for (auto i : listeners) {
    i->received(this, obj);
  }
}
void arc::net::Connection::addListener(NetListener *listener) {
  listeners.push_front(listener);
}