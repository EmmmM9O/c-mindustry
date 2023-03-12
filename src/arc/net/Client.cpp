#pragma once
#include "./Client.hpp"
#include "FrameworkMessage.hpp"
template <typename T>
arc::net::Client<T>::Client(int writeBufferSize, int objectBufferSize,
                            NetSerializer<T> *serialization_)
    : Connection<T>(serialization_, writeBufferSize, objectBufferSize) {
  serialization = serialization_;
}
template <typename T>
void arc::net::Client<T>::connect(int port, std::string host, int time) {
  this->tcp.connect(port, host, time);
  this->udp.connect(port, host);
  thread = std::thread([this]() -> void {
    if (!this->isConnected)
      return;
    while (true) {
      try {
        if (!this->isConnected)
          return;
        java::AnyObject<T> o = this->tcp.readObject();
        if (o.empty())
          break;
        if (!tcpRegistered) {
          if (o.template is<FrameworkMessage::RegisterTCP>()) {
            tcpRegistered = true;
            auto p = FrameworkMessage::RegisterTCP();
            this->sendUDP(p);
            break;
          }
        }
        if (!udpRegistered) {
          if (o.template is<FrameworkMessage::RegisterUDP>()) {
            udpRegistered = true;
            break;
          }
        }
        this->notifyReceived(o);
      } catch (Struct::TimeOut &e) {
        break;
      }
    }
    keepAlive();
  });

  thread.detach();
  this->isConnected = true;
}
template <typename T> void arc::net::Client<T>::keepAlive() {
  if (!this->isConnected)
    return;
  time_t now(0);
  localtime(&now);
  if (difftime(now, time) < 8)
    return;
  localtime(&time);
  this->sendTCP(java::AnyObject<T>(&FrameworkMessage::keepAlive));
  this->sendUDP(java::AnyObject<T>(&FrameworkMessage::keepAlive));
  // std::this_thread::sleep_for(std::chrono::seconds(8));
}
