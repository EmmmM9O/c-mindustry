#pragma once

#include "../../arc/func/Func.hpp"
#include "../../arc/net/FrameworkMessage.cpp"
#include "../../arc/util/Log.cpp"
#include "./Packet.cpp"
#include "./Packets.cpp"
#include "./Streamable.cpp"
#include <boost/any.hpp>
#include <cstddef>
#include <cstdio>
#include <forward_list>
#include <future>
#include <iostream>
#include <map>
#include <math.h>
#include <type_traits>
using namespace mindustry::net::Packets;
using namespace arc::util;
template <typename T, typename T1>
concept IsExtend = std::is_base_of<T1, T>::value;
namespace mindustry {
namespace net {
template <typename T>

class NetProvider {
public:
  virtual void connectClient(std::string ip, int port, void (*success)()) = 0;
  virtual void sendClient(
      java::AnyTwo<
          java::AnyObject<Packet>,
          java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>>
          object,
      bool reliable) {}
  virtual void disconnectClient() {}
};

class Net {
public:
  Net(NetProvider<Packet> &provide);
  NetProvider<Packet> *provider;
  bool active = false;
  bool server = false;
  bool clientLoaded = true;
  static std::map<
      unsigned char,
      java::AnyTwo<java::AnyObject<Packet>,
                   java::AnyObject<
                       arc::net::FrameworkMessage::_FrameworkMessage_>> (*)()>
      packetProvs;
  static byte
  getPacketId(java::AnyTwo<
              java::AnyObject<Packet>,
              java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>>
                  obj);
  std::map<int, Streamable::StreamBuilder> streams;
  std::map<std::string, boost::any> clientListeners;
  template <typename T, Cons<T> F> void handleClient(F listener);
  template <typename T> static void registerPacket(int id);
  static java::AnyTwo<
      java::AnyObject<Packet>,
      java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>> 
  newPacketI(unsigned char id);
  template <is_Packet T> void handleClientReceived(T pac, boost::any obj);
  template <Runnable Run> void connect(std::string ip, int port, Run success);
  void disconnect();
};

} // namespace net
} // namespace mindustry
