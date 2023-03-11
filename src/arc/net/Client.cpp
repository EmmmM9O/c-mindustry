#pragma once
#include "./Client.hpp"

arc::net::Client::Client(int writeBufferSize, int objectBufferSize,
                         NetSerializer *serialization_)
    : Connection(serialization_, writeBufferSize, objectBufferSize) {
  serialization = serialization_;
}
void arc::net::Client::connect(int port, std::string host, int time) {
  tcp.connect(port, host, time);
  udp.connect(port, host);
  thread = std::thread([this]() -> void {
    if (!isConnected)
      return;
    while (true) {
      try {
        if (!isConnected)
          return;
        auto o = tcp.readObject();
        if (o.empty())
          break;
        if (!tcpRegistered) {
          try {
            boost::any_cast<FrameworkMessage::RegisterTCP>(o);
            tcpRegistered = true;
            auto p = FrameworkMessage::RegisterTCP();
            sendUDP(p);
            break;
          } catch (boost::bad_any_cast) {
          }
        }
        if (!udpRegistered) {
          try {
            boost::any_cast<FrameworkMessage::RegisterUDP>(o);
            udpRegistered = true;
            break;
          } catch (boost::bad_any_cast) {
          };
        }

        notifyReceived(o);
      } catch (Struct::TimeOut &e) {

        break;
      }
    }
    keepAlive();
  });

  thread.detach();
  isConnected = true;
}
void arc::net::Client::keepAlive() {
  if (!isConnected)
    return;
  time_t now(0);
  localtime(&now);
  if (difftime(now, time) < 8)
    return;
  localtime(&time);
  sendTCP(FrameworkMessage::keepAlive);
  sendUDP(FrameworkMessage::keepAlive);
  // std::this_thread::sleep_for(std::chrono::seconds(8));
}
