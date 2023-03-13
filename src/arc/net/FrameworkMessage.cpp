#pragma once

#include "./FrameworkMessage.hpp"
const arc::net::FrameworkMessage::DiscoverHost
    arc::net::FrameworkMessage::discoverHost = DiscoverHost();
const arc::net::FrameworkMessage::KeepAlive
    arc::net::FrameworkMessage::keepAlive = KeepAlive();
void arc::net::FrameworkMessage::init() {
  maps.push_back(typeid(_FrameworkMessage_).hash_code());
  maps.push_back(typeid(RegisterUDP).hash_code());
  maps.push_back(typeid(RegisterTCP).hash_code());
  maps.push_back(typeid(KeepAlive).hash_code());
}
bool arc::net::FrameworkMessage::isExtend(boost::any object) {
  if (maps.empty())
    init();
  auto t = object.type().hash_code();
  for (auto i : maps) {
    if (t == i) {
      return true;
    }
  }
  return false;
}

std::vector<size_t> arc::net::FrameworkMessage::maps;