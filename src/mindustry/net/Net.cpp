#pragma once

#include "./Net.hpp"
using namespace mindustry::net::Packets;
using namespace arc::util;
using namespace mindustry::net;
Net::Net(NetProvider &provide) { provider = &provide; }
template <IsExtend<Packet> T> T Net::newPacket(unsigned char id) {
  auto key = id & 0xff;
  if (packetProvs.count(key) <= 0) {
    std::cout << "UnknowKey" << key;
    throw "Unknow Key";
  }
  auto t = packetProvs[key];
  try {
    return boost::any_cast<T (*)()>(t)();
  } catch (boost::bad_any_cast &e) {
    std::cout << "Error from Net::newPacket";
    perror(e.what());
    exit(1);
  }
}
byte Net::getPacketId(boost::any obj) {
  for (auto i : packetProvs) {
    if (i.second.type().hash_code() == obj.type().hash_code()) {
      return i.first;
    }
  }
  return -1;
}
template <typename T, Cons<T> F> void Net::handleClient(F listener) {
  clientListeners[typeid(T).name()] = (void (*)(T))listener;
}
template <is_Packet T> void Net::registerPacket(int id) {
  packetProvs[id] = (T(*)())[]()->T { return T(); };
  packetProvs2[id] = (Packet * (*)())[]()->Packet * { return new T; };
}
Packet *Net::newPacketI(unsigned char id) {
  auto key = id & 0xff;
  if (packetProvs2.count(key) < 0) {
    throw "Error No Packet";
  }
  return packetProvs2[key]();
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

std::map<unsigned char, boost::any> Net::packetProvs;
std::map<unsigned char, Packet *(*)()> Net::packetProvs2;
Streamable::_Streamable_ Streamable::StreamBuilder::build() {
  auto s = Net::newPacket<Streamable::_Streamable_>(type);
  s.stream = stream;
  return s;
}
