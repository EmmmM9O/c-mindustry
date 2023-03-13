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
        java::AnyTwo<java::AnyObject<T>,
                     java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
            o = this->tcp.readObject();
        if (o.key == -1)
          break;
        if (!tcpRegistered) {
          if (o.key == 2 &&
              o.second.template is<FrameworkMessage::RegisterTCP>()) {
            tcpRegistered = true;
            auto p = FrameworkMessage::RegisterTCP();
            java::AnyObject<FrameworkMessage::_FrameworkMessage_> obj(&p);

            java::AnyTwo<java::AnyObject<T>,
                         java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
                temp(obj);
            this->sendUDP(temp);
            break;
          }
        }
        if (!udpRegistered) {
          if (o.key == 2 &&
              o.second.template is<FrameworkMessage::RegisterUDP>()) {
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
  java::AnyObject<FrameworkMessage::_FrameworkMessage_> pa(
      new FrameworkMessage::KeepAlive);
  java::AnyTwo<java::AnyObject<T>,
               java::AnyObject<FrameworkMessage::_FrameworkMessage_>>
      pac(pa);
  this->sendTCP(pac);
  this->sendUDP(pac);
  // std::this_thread::sleep_for(std::chrono::seconds(8));
}
