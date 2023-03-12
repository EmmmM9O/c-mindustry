#pragma once

#include "./Connection.hpp"
template <typename T>
arc::net::Connection<T>::Connection(NetSerializer<T> *serialization,
                                    int writeBufferSize, int objectBufferSize)
    : tcp(serialization, writeBufferSize, objectBufferSize),
      udp(serialization, writeBufferSize) {}
template <typename T> std::string arc::net::Connection<T>::getIP() {
  return tcp.getIP();
}
template <typename T> int arc::net::Connection<T>::getID() { return id; }
template <typename T> bool arc::net::Connection<T>::getIsConnected() {
  return isConnected;
}
template <typename T>
void arc::net::Connection<T>::sendTCP(
    java::AnyTwo<java::AnyObject<T>,
                 java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
        o) {
  tcp.send(o);
}
template <typename T>
void arc::net::Connection<T>::sendUDP(
    java::AnyTwo<java::AnyObject<T>,
                 java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
        o) {
  udp.send(o);
}
template <typename T> void arc::net::Connection<T>::close() {
  isConnected = false;
  tcp.close();
  udp.close();
}
template <typename T>
void arc::net::Connection<T>::notifyReceived(
    java::AnyTwo<java::AnyObject<T>,
                 java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
        obj) {
  for (auto i : listeners) {
    i->received(this, obj);
  }
}
template <typename T>
void arc::net::Connection<T>::addListener(NetListener<T> *listener) {
  listeners.push_front(listener);
}