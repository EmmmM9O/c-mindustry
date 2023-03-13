#pragma once

#include "./Net.hpp"
#include "Streamable.hpp"
using namespace mindustry::net::Packets;
using namespace arc::util;
using namespace mindustry::net;
Net::Net(NetProvider<Packet> &provide) { provider = &provide; }

byte Net::getPacketId(
    java::AnyTwo<
        java::AnyObject<Packet>,
        java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>>
        obj) {
  for (auto i : packetProvs) {
    auto p = i.second();
    if (p.key == obj.key) {
      if (p.key == 1) {
        java::AnyObject<Packet> *f1 = p.first, *f2 = obj.first;
        if (f1->DataAny->type() == f2->DataAny->type())
          return i.first;
      } else if (p.key == 2) {
        java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>
            *f1 = p.second,
            *f2 = obj.second;
        if (f1->DataAny->type() == f2->DataAny->type())
          return i.first;
      }
    }
  }
  return -1;
}
template <typename T, Cons<T> F> void Net::handleClient(F listener) {
  clientListeners[typeid(T).name()] = (void (*)(T))listener;
}
template <typename T> void Net::registerPacket1(int id) {
  packetProvs[id] =
      (java::AnyTwo<
          java::AnyObject<Packet>,
          java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>>(
              *)())[]()
          ->java::AnyTwo<
              java::AnyObject<Packet>,
              java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>> {
		      Log::debug("test6");
    T p;
    Log::debug("test7");
    java::AnyObject<Packet> obj(&p);
    Log::debug("test8:${}",obj.empty());
    return java::AnyTwo<
        java::AnyObject<Packet>,
        java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>>(&obj);
  };
}
template <typename T> void Net::registerPacket2(int id) {
  packetProvs[id] =
      (java::AnyTwo<
          java::AnyObject<Packet>,
          java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>>(
              *)())[]()
          ->java::AnyTwo<
              java::AnyObject<Packet>,
              java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>> {
		      
    return java::AnyTwo<
        java::AnyObject<Packet>,
        java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>>(
        java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>(new T));
  };
}
java::AnyTwo<java::AnyObject<Packet>,
             java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>>
Net::newPacketI(unsigned char id) {
  auto key = id & 0xff;
  if (packetProvs.count(key) <= 0) {
	  Log::debug("No key:${}",(int)key);
    return java::AnyTwo<
        java::AnyObject<Packet>,
        java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>>();
  }
  Log::debug("Test4");
  return packetProvs[key]();
}
template <is_Packet T> void Net::handleClientReceived(T pac, boost::any obj) {
  pac.handled();
  if (obj.type() == typeid(StreamBegin)) {
    auto c = boost::any_cast<StreamBegin>(obj);
    streams[c.id] = Streamable::StreamBuilder(c);
  } else if (obj.type() == typeid(StreamChunk)) {

    auto c = boost::any_cast<StreamChunk>(obj);
    if (streams.count(c.id) <= 0)
      return;
    auto builder = streams[c.id];
    builder.add(c.data);
    if (builder.isDone()) {
      streams.erase(builder.id);
      auto e = builder.build();
      handleClientReceived(e, e);
    }
  } else {
    int p = pac.getPriority();
    if (clientLoaded || p == Packet::priorityHigh) {
      auto key = obj.type().name();
      if (clientListeners.count(key) > 0) {
        auto t = clientListeners[key];
        try {
          boost::any_cast<void (*)(T)>(t)(pac);
        } catch (boost::bad_any_cast &e) {
          perror(e.what());
          exit(1);
        }
      } else {
        pac.handleClient();
      }
    }
  }
}
template <Runnable Run>
void Net::connect(std::string ip, int port, Run success) {
  try {

    provider->connectClient(ip, port, (void (*)())success);
    active = true;
    server = false;
  } catch (...) {
    Log::info("错误!");
  }
}
void Net::disconnect() {
  if (active && !server) {
    Log::info("Disconnecting.");
  }
  provider->disconnectClient();
  server = false;
  active = false;
}

std::map<
    unsigned char,
    java::AnyTwo<
        java::AnyObject<Packet>,
        java::AnyObject<arc::net::FrameworkMessage::_FrameworkMessage_>> (*)()>
    Net::packetProvs;
Streamable::_Streamable_ Streamable::StreamBuilder::build() {
  auto s = Net::newPacketI(type);
  if (s.key != 1 || !s.first->is<Streamable::_Streamable_>())
    return Streamable::_Streamable_();
  auto p = s.first->cast<Streamable::_Streamable_>();
  p.stream = stream;
  return p;
}
